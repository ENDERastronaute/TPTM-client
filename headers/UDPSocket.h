//
// Created by ender on 29/08/2024.
//

#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <atomic>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mutex>

class UDPSocket {
public:
    UDPSocket(const std::string&, int);
    ~UDPSocket();
    void listen();
    void stopListening();
    std::string getClientIp();

    std::mutex mtx;

private:
    std::string ip;
    int port;
    SOCKET sock;
    WSADATA wsaData;
    sockaddr_in sockAddr;
    int sockAddr_len;
    std::atomic<bool> running;
    std::string client_ip;

    int init();
    void close();
};



#endif //UDPSOCKET_H
