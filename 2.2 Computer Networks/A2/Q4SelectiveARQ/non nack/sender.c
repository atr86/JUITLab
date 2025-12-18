// Sender.c - Selective Repeat ARQ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define FRAME_SIZE 1024
#define TIMEOUT_SEC 3
#define MAX_SEQ_NUM 100  // Maximum sequence number

// Global variables
int nextseqnum = 0;  // Next sequence number to be sent

// Frame state structure
typedef struct {
    char frame[FRAME_SIZE];
    time_t sent_time;
    bool acked;
} FrameInfo;

FrameInfo frames[MAX_SEQ_NUM];

int calcChecksum(const char *data)
{
    int checksum = 0;
    for (int i = 0; data[i] != '\0'; i++)
        checksum ^= data[i];
    return checksum;
}

void makeFrame(int seq, const char *data, char *frame)
{
    int checksum = calcChecksum(data);
    sprintf(frame, "<SEQ>%d</SEQ><DATA>%s</DATA><CHK>%d</CHK>", seq, data, checksum);
}

// Check for timeout of individual frames
void checkTimeouts(int sockfd, int base, int nextseqnum)
{
    time_t current_time = time(NULL);
    
    // Process any pending ACKs first before checking timeouts
    receiveACKs(sockfd, base, -1);  // -1 indicates just process ACKs, don't update base
    
    // Give some time to make sure all ACKs are processed
    usleep(200000);  // 200ms wait to allow ACKs to arrive
    
    // Process any new ACKs that arrived during the wait
    receiveACKs(sockfd, base, -1);
    
    for (int i = base; i < nextseqnum; i++) {
        if (!frames[i].acked && (current_time - frames[i].sent_time >= TIMEOUT_SEC)) {
            printf("\n[TIMEOUT] Frame %d timed out. Resending.\n", i);
            send(sockfd, frames[i].frame, strlen(frames[i].frame), 0);
            frames[i].sent_time = current_time;
            printf("[RESENT] %s\n", frames[i].frame);
            
            // Wait a little between retransmissions to avoid overwhelming the network
            usleep(50000);  // 50ms
        }
    }
}

int receiveACKs(int sockfd, int base, int window_size)
{
    fd_set readfds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    timeout.tv_sec = 0;  // Non-blocking check
    timeout.tv_usec = 500000;  // 500ms - increased from 100ms to allow more time to receive ACKs
    
    char buffer[FRAME_SIZE * 10];  // Larger buffer to handle multiple ACKs
    memset(buffer, 0, sizeof(buffer));
    
    int new_base = base;
    int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
    
    if (activity > 0) {
        int val = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (val > 0) {
            buffer[val] = '\0';
            
            // Process potentially multiple ACKs in the buffer
            char *ack_start = buffer;
            while ((ack_start = strstr(ack_start, "<ACK>")) != NULL) {
                int ack_seq;
                if (sscanf(ack_start, "<ACK>%d</ACK>", &ack_seq) == 1) {
                    printf("[RECV] ACK %d\n", ack_seq);
                    
                    // Mark this frame as acknowledged
                    if (ack_seq >= base && ack_seq < nextseqnum) {
                        frames[ack_seq].acked = true;
                    }
                    
                    // Move to the next ACK
                    ack_start += 5;  // Skip past "<ACK>"
                }
            }
            
            // Check if we can advance the base (if not just processing ACKs)
            if (window_size != -1) {
                while (new_base < nextseqnum && frames[new_base].acked) {
                    new_base++;
                }
                
                if (new_base > base) {
                    printf("[WINDOW] Advanced base to %d, window is now %d to %d\n", 
                           new_base, new_base, new_base + window_size - 1);
                }
            }
        }
    }
    
    return new_base;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <receiver_ip> <port> <window_size>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int window_size = atoi(argv[3]);

    int sockfd;
    struct sockaddr_in serv_addr;
    char input[256];
    int base = 0;
    nextseqnum = 0;  // Initialize global variable

    // Initialize frame status
    for (int i = 0; i < MAX_SEQ_NUM; i++) {
        frames[i].acked = false;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }
    printf("Connected to receiver.\n");

    // Send initial window of frames
    printf("Enter initial %d messages:\n", window_size);
    for (int i = 0; i < window_size; i++) {
        printf("Enter message for Frame %d: ", nextseqnum);
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = '\0';
        
        makeFrame(nextseqnum, input, frames[nextseqnum].frame);
        send(sockfd, frames[nextseqnum].frame, strlen(frames[nextseqnum].frame), 0);
        frames[nextseqnum].sent_time = time(NULL);
        frames[nextseqnum].acked = false;
        
        printf("[SENT] %s\n", frames[nextseqnum].frame);
        nextseqnum++;
    }

    while (1) {
        // Process incoming ACKs first
        int new_base = receiveACKs(sockfd, base, window_size);
        if (new_base > base) {
            base = new_base;
        }
        
        // Check for timeouts and resend individual frames if needed
        checkTimeouts(sockfd, base, nextseqnum);
        
        // Send new frames if window space is available
        while (nextseqnum < base + window_size) {
            printf("\nEnter message for Frame %d: ", nextseqnum);
            fgets(input, 256, stdin);
            input[strcspn(input, "\n")] = '\0';
            
            makeFrame(nextseqnum, input, frames[nextseqnum].frame);
            send(sockfd, frames[nextseqnum].frame, strlen(frames[nextseqnum].frame), 0);
            frames[nextseqnum].sent_time = time(NULL);
            frames[nextseqnum].acked = false;
            
            printf("[SENT] %s\n", frames[nextseqnum].frame);
            nextseqnum++;
        }

        // Small sleep to prevent CPU hogging
        usleep(50000);  // 50ms
    }

    close(sockfd);
    return 0;
}
