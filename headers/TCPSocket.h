//
// Created by ender on 29/08/2024.
//

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <atomic>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include "EFTP.h"

class TCPSocket {
public:
    TCPSocket(const std::string&, int);

    ~TCPSocket();

    void listen() const;

    int connectToServer(const std::string&, int) const;

    void stop();

    void stopListening();
    std::string getClientIp();

private:
    std::string ip;
    int port;
    SOCKET sock;
    WSADATA wsaData;
    sockaddr_in sockAddr;
    int sockAddr_len;
    std::string client_ip;
    std::atomic<bool> running;

    int init();
    void close() const;
};



#endif //TCPSOCKET_H
