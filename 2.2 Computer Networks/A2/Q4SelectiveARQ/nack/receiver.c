// Receiver.c - Selective Repeat ARQ with NACKs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdbool.h>
#include <netinet/tcp.h>  // For TCP_NODELAY

#define FRAME_SIZE 1024
#define MAX_SEQ_NUM 100  // Maximum sequence number
#define RWS 10           // Default receiver window size

int LOSS_PROBABILITY;
bool received_frames[MAX_SEQ_NUM];  // To track which frames have been received
char frame_data[MAX_SEQ_NUM][256];  // To store received frame data
int expected_seq_numbers[MAX_SEQ_NUM]; // Track expected sequence numbers within window

int calcChecksum(const char *data)
{
    int checksum = 0;
    for (int i = 0; data[i] != '\0'; i++)
        checksum ^= data[i];
    return checksum;
}

int simulateLoss()
{
    return (rand() % 100) < LOSS_PROBABILITY;
}

void sendACK(int sockfd, int seq)
{
    char ack[50];
    sprintf(ack, "<ACK>%d</ACK>", seq);
    
    // Add a small delay to avoid ACKs getting bundled/dropped
    usleep(10000);  // 10ms
    
    // Send with TCP_NODELAY to ensure immediate transmission
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
    
    send(sockfd, ack, strlen(ack), 0);
    printf("[SENT] ACK %d\n", seq);
    
    // Flush output buffer to ensure ACK is sent
    fsync(sockfd);
}

void sendNACK(int sockfd, int seq)
{
    char nack[50];
    sprintf(nack, "<NACK>%d</NACK>", seq);
    
    // Add a small delay to avoid NACKs getting bundled/dropped
    usleep(10000);  // 10ms
    
    // Send with TCP_NODELAY to ensure immediate transmission
    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
    
    send(sockfd, nack, strlen(nack), 0);
    printf("[SENT] NACK %d\n", seq);
    
    // Flush output buffer to ensure NACK is sent
    fsync(sockfd);
}

void updateExpectedSeqNumbers(int base, int window_size)
{
    for (int i = 0; i < window_size; i++) {
        expected_seq_numbers[i] = base + i;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
    {
        printf("Usage: %s <port> <loss_probability> [window_size]\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    LOSS_PROBABILITY = atoi(argv[2]);
    int window_size = (argc == 4) ? atoi(argv[3]) : RWS;

    if (LOSS_PROBABILITY < 0 || LOSS_PROBABILITY > 100)
    {
        printf("Loss probability must be between 0 and 100.\n");
        return 1;
    }

    // Initialize received frames tracking
    for (int i = 0; i < MAX_SEQ_NUM; i++) {
        received_frames[i] = false;
    }
    
    // Initialize expected sequence numbers within window
    updateExpectedSeqNumbers(0, window_size);

    srand(time(NULL));

    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_len = sizeof(cli_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 1);

    printf("Waiting for sender on port %d with loss probability %d%%...\n", port, LOSS_PROBABILITY);
    printf("Using window size of %d\n", window_size);
    
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &addr_len);
    printf("Sender connected.\n");

    char buffer[FRAME_SIZE];
    int base = 0;  // Lower edge of the receiver window

    while (1)
    {
        int val = recv(newsockfd, buffer, FRAME_SIZE, 0);
        if (val <= 0)
            break;

        buffer[val] = '\0';
        int seq, recv_chk;
        char data[256];

        if (sscanf(buffer, "<SEQ>%d</SEQ><DATA>%[^<]</DATA><CHK>%d</CHK>", &seq, data, &recv_chk) == 3)
        {
            printf("\n[RECV] Frame %d: %s\n", seq, data);

            // Check if frame is within receiver window
            if (seq >= base && seq < base + window_size)
            {
                bool isCorrupt = simulateLoss();
                if (isCorrupt)
                {
                    printf("[CORRUPT FRAME] Simulating corruption of Frame %d\n", seq);
                    recv_chk += 1; // Corrupt checksum
                }

                int chk = calcChecksum(data);

                if (chk == recv_chk)
                {
                    printf("[ACCEPTED] Frame %d OK\n", seq);
                    
                    // Store the frame if not already received
                    if (!received_frames[seq]) {
                        received_frames[seq] = true;
                        strcpy(frame_data[seq], data);
                        
                        // Deliver in-order frames to upper layer and advance window
                        while (received_frames[base]) {
                            printf("[DELIVER] Frame %d to upper layer: %s\n", base, frame_data[base]);
                            base++;
                        }
                        
                        // Update expected sequence numbers after window advancement
                        updateExpectedSeqNumbers(base, window_size);
                        printf("[WINDOW] Receiver window is now %d to %d\n", base, base + window_size - 1);
                    } else {
                        printf("[DUPLICATE] Already received Frame %d\n", seq);
                    }
                    
                    // Send ACK for correctly received frame
                    sendACK(newsockfd, seq);
                }
                else
                {
                    printf("[REJECTED] Frame %d has invalid checksum\n", seq);
                    // Send NACK for corrupted frame
                    sendNACK(newsockfd, seq);
                }
            }
            else if (seq < base)
            {
                // Frame is before the window, might be a retransmission of an already acknowledged frame
                printf("[DUPLICATE] Frame %d is already acknowledged\n", seq);
                
                // Send ACK again to ensure sender gets it
                sendACK(newsockfd, seq);
            }
            else
            {
                // Frame is beyond the current window
                printf("[OUT OF WINDOW] Frame %d is beyond current window (%d to %d)\n", 
                       seq, base, base + window_size - 1);
                // No ACK/NACK sent for out-of-window frames
            }
        }
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
