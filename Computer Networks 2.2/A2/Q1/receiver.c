#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 1024

typedef struct {
    char data[MAX_DATA_SIZE];
} Frame;

void WaitForEvent() {
    printf("[Receiver] Waiting for frame...\n");
}

void ReceiveFrameOverTCP(Frame* frame_out, int port) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return;
    }

    listen(server_fd, 1);
    printf("[Receiver] Listening on port %d...\n", port);

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        return;
    }

    recv(client_fd, frame_out, sizeof(Frame), 0);
    printf("[Receiver] Frame received.\n");

    close(client_fd);
    close(server_fd);
}

Frame ReceiveFrame(int port ){
    Frame frame;
    ReceiveFrameOverTCP(&frame, port);
    return frame;
}

void ExtractData(Frame frame, char* data_out) {
    strncpy(data_out, frame.data, MAX_DATA_SIZE);
}

void DeliverData(const char* data) {
    printf("[Receiver] Delivered data to upper layer: \"%s\"\n", data);
}

int main(int argc, char* argv[]) {
if (argc < 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int portno = atoi(argv[1]);
    printf("---- Receiver (TCP) ----\n\n");
    char data[MAX_DATA_SIZE];
    WaitForEvent();
    Frame frame = ReceiveFrame(portno);
    ExtractData(frame, data);
    DeliverData(data);
    return 0;
}

