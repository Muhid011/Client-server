#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9001
#define SIZE 255

int main() {
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char filename[SIZE];
    char response[SIZE];

    // Start Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == INVALID_SOCKET) {
        printf("Socket error\n");
        return 1;
    }

    // Server setup
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Could not connect to server\n");
        return 1;
    }

    // Ask for file name
    printf("Enter file name: ");
    scanf("%s", filename);

    // Send file name
    send(clientSocket, filename, strlen(filename), 0);

    // Receive response
    memset(response, 0, SIZE);
    recv(clientSocket, response, SIZE, 0);

    printf("\nServer says:\n%s\n", response);

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}