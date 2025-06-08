#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<stdlib.h>
#define MAX_DATA_SIZE 1024

typedef struct {
    int seq;
    char data[MAX_DATA_SIZE];
} Frame;

typedef struct {
    int ack;
} Ack;


void WaitForEventSender() {
    printf("[Sender] Waiting for request...\n");
    sleep(1);
}

void GetData(char* buffer) {
    printf("[Sender] Enter data to send (type 'exit' to quit): ");
    fgets(buffer, MAX_DATA_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
}

Frame MakeFrame(const char* data, int seq) {
    Frame frame;
    frame.seq = seq;
    strncpy(frame.data, data, MAX_DATA_SIZE);
    return frame;
}

void SendFrameOverTCP(Frame frame, const char* ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    Ack ack;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        return;
    }

    // Send the frame
    send(sockfd, &frame, sizeof(Frame), 0);
    printf("[Sender] Sent frame with seq: %d, data: \"%s\"\n", frame.seq, frame.data);

    // Wait for ACK
    recv(sockfd, &ack, sizeof(Ack), 0);
    printf("[Sender] Received ACK: %d\n", ack.ack);

    if (ack.ack != frame.seq) {
        printf("[Sender] Unexpected ACK. Resending frame (not needed in noiseless channel).\n");
    }

    close(sockfd);
}

void Sender(const char* ip, int port) {
    char buffer[MAX_DATA_SIZE];
    int seq = 0;

    while (1) {
        WaitForEventSender();
        GetData(buffer);

        if (strcmp(buffer, "exit") == 0) {
            printf("[Sender] Exiting...\n");
            break;
        }


        Frame frame = MakeFrame(buffer, seq);
        SendFrameOverTCP(frame, ip,port);
        seq = (seq + 1) % 2; // Toggle between 0 and 1 for stop-and-wait
    }
}

int main(int argc , char* argv[]) {
	if (argc < 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }
 	int portno= atoi(argv[2]);
    printf("---- Stop-and-Wait Protocol Sender (TCP) ----\n\n");
    Sender(argv[1],portno);
    return 0;
}



