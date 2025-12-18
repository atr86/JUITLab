// sender.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

typedef struct {
    char data[MAX_DATA_SIZE];
} Frame;

void WaitForEvent() {
    printf("[Sender] Waiting for request...\n");
    sleep(1);
}

void GetData(char* buffer) {
    printf("[Sender] Enter data to send: ");
    fgets(buffer, MAX_DATA_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';// put only 1st line
}

Frame MakeFrame(const char* data) {
    Frame frame;
    strncpy(frame.data, data, MAX_DATA_SIZE);
    return frame;
}

void SendFrameOverTCP(Frame frame, const char* ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        return;
    }

    send(sockfd, &frame, sizeof(Frame), 0);
    printf("[Sender] Frame sent: \"%s\"\n", frame.data);
    close(sockfd);
}

void SendFrame(Frame frame,const char* ip,int port) {
    SendFrameOverTCP(frame,ip,port);
}


int main(int argc, char* argv[]) {
    int portno;
    

    if (argc < 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);
    printf("---- Sender ----\n\n");
    char buffer[MAX_DATA_SIZE];
    WaitForEvent();
    GetData(buffer);
    Frame frame = MakeFrame(buffer);
    SendFrame(frame,(argv[1]),portno);
    return 0;
}

