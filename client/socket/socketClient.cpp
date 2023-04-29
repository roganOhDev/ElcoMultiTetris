//
// Created by Oh DongGeun on 2023/04/27.
//

#include "socketClient.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

#define PORT 8888
#define MAX_BUFFER_SIZE 1024

void setupServer(sockaddr_in &serv_addr);

int convertAddressToBinary(sockaddr_in &serv_addr);

int connectToServer(int sock, sockaddr_in &serv_addr);

int socketSelect(int sock, fd_set &read_fds, fd_set &write_fds);

int recieveData(int sock, int valread, char *buffer, fd_set &read_fds);

int sendMessage(int sock, char *message, fd_set &read_fds);

int socket() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char message[MAX_BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Set up server address
    setupServer(serv_addr);

    // Convert IPv4 and IPv6 addresses from text to binary form
    int convertResult = convertAddressToBinary(serv_addr);
    if (convertResult < 0) {
        return -1;
    }

    // Connect to server
    int connectResult = connectToServer(sock, serv_addr);
    if (connectResult < 0) {
        return -1;
    }

    // Add socket to select set
    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_SET(sock, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    while (true) {
        int socketSelectResult = socketSelect(sock, read_fds, write_fds);
        if (socketSelectResult < 0) {
            break;
        }

        valread = recieveData(sock, valread, buffer, read_fds);
        if (valread < 0) {
            break;
        }

        int sendResult = sendMessage(sock, message, read_fds);
        if (sendResult < 0) {
            break;
        }

        FD_ZERO(&read_fds);
        FD_SET(sock, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
    }

    // Close socket
    try {
        close(sock);
    }
    catch (std::exception &e) {
        std::cerr << "Error closing socket" << std::endl;
        return -1;
    }

    return 0;
}

int sendMessage(int sock, char *message, fd_set &read_fds) {
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        if (fgets(message, MAX_BUFFER_SIZE, stdin) == NULL) {
            std::cerr << "Error reading standard input" << std::endl;
            return -1;
        }

        if (send(sock, message, strlen(message), 0) < 0) {
            std::cerr << "Send failed" << std::endl;
            return -1;
        }
    }
    return 0;
}

int recieveData(int sock, int valread, char *buffer, fd_set &read_fds) {
    if (FD_ISSET(sock, &read_fds)) {
        valread = read(sock, buffer, MAX_BUFFER_SIZE);
        if (valread <= 0) {
            std::cerr << "Server disconnected" << std::endl;
            return -1;
        }

        std::cout << "Received data: " << buffer << std::endl;

        memset(buffer, 0, MAX_BUFFER_SIZE);
    }

    return valread;
}

int socketSelect(int sock, fd_set &read_fds, fd_set &write_fds) {
    int activity = select(std::max(sock, STDIN_FILENO) + 1, &read_fds, &write_fds, NULL, NULL);
    if ((activity < 0) && (errno != EINTR)) {
        std::cerr << "Select error" << std::endl;
        return -1;
    }
    return 0;
}

int connectToServer(int sock, sockaddr_in &serv_addr) {
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }
    return 1;
}

int convertAddressToBinary(sockaddr_in &serv_addr) {
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }
    return 1;
}

void setupServer(sockaddr_in &serv_addr) {
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
}

