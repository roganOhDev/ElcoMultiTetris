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

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char message[MAX_BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // Set up server address
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);


    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    // Add socket to select set
    fd_set read_fds, write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    FD_SET(sock, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    while (true)
    {
        int activity = select(std::max(sock, STDIN_FILENO) + 1, &read_fds, &write_fds, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
        {
            std::cerr << "Select error" << std::endl;
            return -1;
        }

        if (FD_ISSET(sock, &read_fds))
        {
            valread = read(sock, buffer, MAX_BUFFER_SIZE);
            if (valread <= 0)
            {
                std::cerr << "Server disconnected" << std::endl;
                break;
            }

            std::cout << "Received data: " << buffer << std::endl;

            memset(buffer, 0, MAX_BUFFER_SIZE);
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            if (fgets(message, MAX_BUFFER_SIZE, stdin) == NULL)
            {
                std::cerr << "Error reading standard input" << std::endl;
                break;
            }

            if (send(sock, message, strlen(message), 0) < 0)
            {
                std::cerr << "Send failed" << std::endl;
                return -1;
            }
        }

        FD_ZERO(&read_fds);
        FD_SET(sock, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
    }

    // Close socket
    close(sock);

    return 0;
}