#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 80
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0) {
        printf("Bind failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) != 0) {
        printf("Listen failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port %d...\n", SERVER_PORT);

    while (1) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            printf("Accept failed.\n");
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        char buffer[BUFFER_SIZE];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';  // Null-terminate the received data
            printf("Received data: %s\n", buffer);
        }

        closesocket(clientSocket);
    }

    // This server runs indefinitely and never reaches this point, but the
    // closesocket and WSACleanup calls are included for completeness
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
