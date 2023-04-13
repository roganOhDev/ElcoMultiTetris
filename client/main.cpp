
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <pcap/socket.h>
#include <sys/socket.h>
#include <iconv.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include <thread>
//#include <pcap/socket.h>
#define PACKET_SIZE 1024

using namespace std;

//std::string convertToString(char *buffer, size_t length) {
//    std::string result;
//    iconv_t conversionDescriptor = iconv_open("UTF-8", "UTF-8");
//    if (conversionDescriptor == (iconv_t) (-1)) {
//        return result;
//    }
//
//    char *input = buffer;
//    size_t inputLength = length;
//    char output[1024]; // set the size of the output buffer as needed
//    char *outputPtr = output;
//    size_t outputLength = sizeof(output);
//
//    while (inputLength > 0) {
//        if (iconv(conversionDescriptor, &input, &inputLength, &outputPtr, &outputLength) == (size_t) (-1)) {
//            break;
//        }
//    }
//
//    iconv_close(conversionDescriptor);
//    result = std::string(output, outputPtr - output);
//    return result;
//}

void proc_recv(int clientSocket) {
    string cmd; //string 생성
    char buffer[PACKET_SIZE];
    int numBytesReceived = recv(clientSocket, buffer, PACKET_SIZE, 0);

    std::string recievedData(buffer, numBytesReceived);
    std::cout << "Received data from server: " << recievedData << '\n';
}

void proc_send(int clientSocket) {
//    const char *data = "Hello from client";
    char data[PACKET_SIZE];
    std::cin >> data;

    int bytesSent = send(clientSocket, data, strlen(data), 0);
    std::cout << "Sent " << bytesSent << " bytes to server\n";
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8981);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int result = connect(clientSocket, (sockaddr *) &serverAddr, sizeof(serverAddr));
    if (result != 0) {
        std::cerr << "Failed to connect to server\n";
        return 1;
    }

    thread recv(proc_recv, clientSocket);

    thread send(proc_send, clientSocket);

    while (1) {
        recv.join();
        send.join();
    }
    close(clientSocket);
    return 0;
}
//select poll epoll kqueue