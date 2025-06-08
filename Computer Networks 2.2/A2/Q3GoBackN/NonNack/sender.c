// Sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>

#define FRAME_SIZE 1024
#define TIMEOUT_SEC 3

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

int waitForACKs(int sockfd, int *base, int ws)
{
    fd_set readfds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;

    int activity = select(sockfd + 1, &readfds, NULL, NULL, &timeout);
    if (activity > 0)
    {
        char buffer[FRAME_SIZE];
        int val;
        while ((val = recv(sockfd, buffer, FRAME_SIZE, MSG_DONTWAIT)) > 0)
        {
            buffer[val] = '\0';
            int ack_seq;
            if (sscanf(buffer, "<ACK>%d</ACK>", &ack_seq) == 1)
            {
                printf("\n[RECV] Received upto ACK %d, window size increased to %d\n", ack_seq, (ack_seq + ws));
                if (ack_seq >= *base)
                {
                    *base = ack_seq + 1;
                }
            }
        }
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <receiver_ip> <port> <window_size>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int window_size = atoi(argv[3]);

    int sockfd;
    struct sockaddr_in serv_addr;
    char input[256];
    char frames[100][FRAME_SIZE];
    int base = 0, nextseqnum = 0;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address / Address not supported");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connection Failed");
        return -1;
    }
    printf("Connected to receiver.\n");

    printf("Enter initial %d messages:\n", window_size);
    for (int i = 0; i < window_size; i++)
    {
        printf("Enter message for Frame %d: ", nextseqnum);
        fgets(input, 256, stdin);
        input[strcspn(input, "\n")] = '\0';
        makeFrame(nextseqnum, input, frames[nextseqnum]);
        send(sockfd, frames[nextseqnum], strlen(frames[nextseqnum]), 0);
        printf("[SENT] %s\n", frames[nextseqnum]);
        nextseqnum++;
    }

    while (1)
    {
        if (waitForACKs(sockfd, &base, window_size))
        {
            while (nextseqnum < base + window_size)
            {
                printf("\nEnter message for Frame %d: ", nextseqnum);
                fgets(input, 256, stdin);
                input[strcspn(input, "\n")] = '\0';
                makeFrame(nextseqnum, input, frames[nextseqnum]);
                send(sockfd, frames[nextseqnum], strlen(frames[nextseqnum]), 0);
                printf("[SENT] %s\n", frames[nextseqnum]);
                nextseqnum++;
            }
        }
        else
        {
            printf("\n\n[TIMEOUT] ACK not received. Resending window from Frame %d\n", base);
            for (int i = base; i < nextseqnum; i++)
            {
                send(sockfd, frames[i], strlen(frames[i]), 0);
                printf("[RESENT] %s\n", frames[i]);
            }
        }
    }

    close(sockfd);
    return 0;
}
