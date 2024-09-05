//
// Created by ender on 29/08/2024.
//

#include "UDPSocket.h"

#include <iostream>

UDPSocket::UDPSocket(const std::string& ip, int port)
: ip(ip), port(port), sock(), wsaData(), sockAddr(), sockAddr_len(sizeof(sockAddr)), running(true)
{
    init();
}

UDPSocket::~UDPSocket() {
    close();
}

int UDPSocket::init() {
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR) {
        return 1;
    }

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock == INVALID_SOCKET) {
        return 1;
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &sockAddr.sin_addr);

    if (bind(sock, (SOCKADDR*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
        return 1;
    }

    sockAddr_len = sizeof(sockAddr);

    return 0;
}

void UDPSocket::close() {
    running = false;

    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }

    WSACleanup();
}

void UDPSocket::listen() {
    sockaddr_in reqAddr {};
    int reqAddr_len = sizeof(reqAddr);

    while (running) {
        char buffer[1024];
        int result = recvfrom(sock, buffer, sizeof(buffer), 0, (SOCKADDR*)&reqAddr, &reqAddr_len);

        if (result == SOCKET_ERROR) {
            continue;
        }

        std::string message(buffer, result);
        char temp_client_ip[INET_ADDRSTRLEN];

        std::cout << message << std::endl;



        inet_ntop(AF_INET, &reqAddr.sin_addr, temp_client_ip, INET_ADDRSTRLEN);

        {
            std::lock_guard lock(mtx);
            client_ip = temp_client_ip;
        }
    }
}

void UDPSocket::stopListening() {
    running = false;
}

std::string UDPSocket::getClientIp() {
    return client_ip;
}

