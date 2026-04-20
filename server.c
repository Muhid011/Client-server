#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <signal.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9001
#define SIZE 255

SOCKET serverSocket;

int main() {
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char filename[SIZE];
    char buffer[SIZE];

    // Start Winsock
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET) {
        printf("Socket error\n");
        return 1;
    }

    // Server setup
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("Bind failed\n");
        return 1;
    }

    listen(serverSocket, 5);
    printf("Server is running...\n");

    while (1) {
        printf("\nWaiting for client...\n");

        clientSocket = accept(serverSocket, NULL, NULL);

        memset(filename, 0, SIZE);
        recv(clientSocket, filename, SIZE, 0);

        printf("Client asked for file: %s\n", filename);

        FILE *file = fopen(filename, "r");

        if (file == NULL) {
            char *msg = "File not found";
            send(clientSocket, msg, strlen(msg), 0);
        } else {
            memset(buffer, 0, SIZE);

            fread(buffer, 1, SIZE - 1, file);
            fclose(file);

            if (strlen(buffer) == 0) {
                char *msg = "File is empty";
                send(clientSocket, msg, strlen(msg), 0);
            } else {
                send(clientSocket, buffer, strlen(buffer), 0);
            }
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}