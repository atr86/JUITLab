// Sender.c - Selective Repeat ARQ with NACKs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <netinet/tcp.h>

#define FRAME_SIZE 1024
#define MAX_SEQ_NUM 100  // Maximum sequence number

// Global variables
int nextseqnum = 0;  // Next sequence number to be sent

// Frame state structure
typedef struct {
    char frame[FRAME_SIZE];
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

int processAcknowledgements(int sockfd, int base, int window_size)
{
    fd_set readfds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;  // 100ms
    
    char buffer[FRAME_SIZE * 10];  // Large buffer to handle multiple ACKs/NACKs
    memset(buffer, 0, sizeof(buffer));
    
    int new_base = base;
    int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
    
    if (activity > 0) {
        int val = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (val > 0) {
            buffer[val] = '\0';
            
            // Process ACKs in the buffer
            char *ack_ptr = buffer;
            while ((ack_ptr = strstr(ack_ptr, "<ACK>")) != NULL) {
                int ack_seq;
                if (sscanf(ack_ptr, "<ACK>%d</ACK>", &ack_seq) == 1) {
                    printf("[RECV] ACK %d\n", ack_seq);
                    
                    // Mark this frame as acknowledged
                    if (ack_seq >= base && ack_seq < nextseqnum) {
                        frames[ack_seq].acked = true;
                    }
                    
                    // Move to the next ACK
                    ack_ptr += 5;  // Skip past "<ACK>"
                }
            }
            
            // Process NACKs in the buffer
            char *nack_ptr = buffer;
            while ((nack_ptr = strstr(nack_ptr, "<NACK>")) != NULL) {
                int nack_seq;
                if (sscanf(nack_ptr, "<NACK>%d</NACK>", &nack_seq) == 1) {
                    printf("[RECV] NACK %d - Retransmitting frame\n", nack_seq);
                    
                    // Retransmit the requested frame if it's in our window
                    if (nack_seq >= base && nack_seq < nextseqnum) {
                        send(sockfd, frames[nack_seq].frame, strlen(frames[nack_seq].frame), 0);
                        printf("[RESENT] %s\n", frames[nack_seq].frame);
                    }
                    
                    // Move to the next NACK
                    nack_ptr += 6;  // Skip past "<NACK>"
                }
            }
            
            // Check if we can advance the base
            while (new_base < nextseqnum && frames[new_base].acked) {
                new_base++;
            }
            
            if (new_base > base) {
                printf("[WINDOW] Advanced base to %d, window is now %d to %d\n", 
                       new_base, new_base, new_base + window_size - 1);
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

    // Set TCP_NODELAY to send packets immediately
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));

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
        frames[nextseqnum].acked = false;
        
        printf("[SENT] %s\n", frames[nextseqnum].frame);
        nextseqnum++;
        
        // Small delay between frames
        usleep(10000);  // 10ms
    }

    while (1) {
        // Process incoming ACKs and NACKs
        int new_base = processAcknowledgements(sockfd, base, window_size);
        if (new_base > base) {
            base = new_base;
        }
        
        // Send new frames if window space is available
        while (nextseqnum < base + window_size) {
            printf("\nEnter message for Frame %d: ", nextseqnum);
            fgets(input, 256, stdin);
            input[strcspn(input, "\n")] = '\0';
            
            makeFrame(nextseqnum, input, frames[nextseqnum].frame);
            send(sockfd, frames[nextseqnum].frame, strlen(frames[nextseqnum].frame), 0);
            frames[nextseqnum].acked = false;
            
            printf("[SENT] %s\n", frames[nextseqnum].frame);
            nextseqnum++;
            
            // Small delay between frames
            usleep(10000);  // 10ms
        }

        // Small sleep to prevent CPU hogging
        usleep(50000);  // 50ms
    }

    close(sockfd);
    return 0;
}
