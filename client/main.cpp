#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <pcap/socket.h>

#define PACKET_SIZE 1024
SOCKET skt;
using namespace std;

void proc_recv() {
    char buffer[PACKET_SIZE] = {}; //char 생성
    string cmd; //string 생성
    while (1) {
        for (int i = 0; i<PACKET_SIZE; i++) {
            buffer[i] = NULL;
        }
        recv(skt, buffer, PACKET_SIZE, 0); //데이터받아오기
        cmd = buffer; //buffer의값이 cmd에 들어갑니다
        if (cmd == "hi") break; //cmd의값이 "exit"일경우 데이터받아오기'만' 종료
        cout << "받은 메세지: " << buffer << endl;
    }
}

int main() {
    // Create socket
    skt = socket(AF_INET, SOCK_STREAM, 0);
    if (skt == -1) {
        std::cerr << "Could not create socket\n";
        return 1;
    }

    // Set server address and port
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with server IP address
    server.sin_family = AF_INET;
    server.sin_port = htons(12345); // Replace with server port number

    // Connect to server
    if (connect(skt, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection error\n";
        return 1;
    }

    struct timeval timeout;
    timeout.tv_sec = 5; // 5 seconds
    timeout.tv_usec = 0;
    setsockopt(skt, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    thread proc1(proc_recv);
    // Send and receive data
//    char message[256] ="Mmessage";
//    while (true) {
//        if (send(sock, message, strlen(message), 0) < 0) {
//            std::cerr << "Send failed\n";
//            return 1;
//        }
//
//        char server_reply[256];
//        if (recv(sock, server_reply, 256,0) < 0) {
//            std::cout << "recevie fail";
//        }
//        std::cout << "Server reply: " << server_reply << "\n";
//
//        char ack_message[256] = "Ack";
//        if (send(sock, ack_message, strlen(ack_message), 0) < 0) {
//            std::cerr << "Send acknowledgment failed\n";
//            return 1;
//        }
//    }
    proc1.join();
    // Close socket
    close(skt);
    return 0;
}