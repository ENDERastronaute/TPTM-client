//
// Created by ender on 29/08/2024.
//

#include "TCPSocket.h"

#include <iostream>

#include "FileManager.h"

TCPSocket::TCPSocket(const std::string& ip, int port)
: ip(ip), port(port), sock(), wsaData(), sockAddr(), sockAddr_len(sizeof(sockAddr)), running(true)
{
    init();
}

TCPSocket::~TCPSocket() {
    close();
}

int TCPSocket::init() {
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR) {
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

int TCPSocket::connectToServer(const std::string& server_ip, int server_port) const {
    sockaddr_in serverAddr {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(server_port);
    serverAddr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        return 1;
    }

    return 0;
}

void TCPSocket::close() const {

    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }

    WSACleanup();
}

void TCPSocket::listen() const {
    while (running) {
        char header[255];

        int result = recv(sock, header, sizeof(header), 0);

        std::cout << result;

        if (result <= 0) {
            break;
        }

        unsigned char type = header[0];

        if (type == EFTSEND) {
            std::vector<unsigned char> pathBytes(header + 3, header + 3 + header[2]);
            std::string path(pathBytes.begin(), pathBytes.end());

            FileManager::writeFile(sock, path, header[1]);
        }
    }
}

void TCPSocket::stop() {
    running = false;
}