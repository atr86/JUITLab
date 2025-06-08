// Receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define FRAME_SIZE 1024

int LOSS_PROBABILITY;

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
    send(sockfd, ack, strlen(ack), 0);
    printf("[SENT] ACK %d\n", seq);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <port> <loss_probability>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    LOSS_PROBABILITY = atoi(argv[2]);

    if (LOSS_PROBABILITY < 0 || LOSS_PROBABILITY > 100)
    {
        printf("Loss probability must be between 0 and 100.\n");
        return 1;
    }

    srand(time(0));

    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t addr_len = sizeof(cli_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 1);

    printf("Waiting for sender on port %d with loss probability %d...\n", port, LOSS_PROBABILITY);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &addr_len);
    printf("Sender connected.\n");

    char buffer[FRAME_SIZE];
    int expected_seq = 0;

    while (1)
    {
        int val = recv(newsockfd, buffer, FRAME_SIZE, 0);
        if (val <= 0)
            break;

        buffer[val] = '\0';
        int seq, recv_chk;
        char data[100];

        if (sscanf(buffer, "<SEQ>%d</SEQ><DATA>%[^<]</DATA><CHK>%d</CHK>", &seq, data, &recv_chk) == 3)
        {
            printf("\n\n[RECV] Frame %d: %s\n", seq, data);

            if (simulateLoss())
            {
                printf("[CORRUPT FRAME] Simulating corruption of Frame %d\n", seq);
                recv_chk += 1; // Corrupt checksum
            }

            int chk = calcChecksum(data);

            if (seq == expected_seq && chk == recv_chk)
            {
                printf("[ACCEPTED] Frame %d OK\n", seq);
                sendACK(newsockfd, seq);
                expected_seq++;
            }
            else
            {
                printf("[REJECTED] Frame %d Wrong seq or checksum\n", seq);
                // No ACK sent
            }
        }
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
