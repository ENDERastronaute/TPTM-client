//
// Created by ender on 29/08/2024.
//

#include "TCPSocket.h"

#include <iostream>

#include "FileManager.h"

/**
 * Creates a new socket.
 * @param ip The interface's IP.
 * @param port The port.
 */
TCPSocket::TCPSocket(const std::string& ip, int port)
: ip(ip), port(port), sock(), wsaData(), sockAddr(), sockAddr_len(sizeof(sockAddr)), running(true)
{
    init();
}

/**
 * Automatically closes and flushes the socket.
 */
TCPSocket::~TCPSocket() {
    close();
}

/**
 * Init the socket for future usage.
 * @return 0 if it successfully inited the socket, 1 if there was an error.
 */
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

/**
 * 
 * @param server_ip the remote IP.
 * @param server_port The remote port.
 * @return 0 if it successfully connected, 1 if there was an error.
 */
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

/**
 * Closes and flushes the socket.
 */
void TCPSocket::close() const {

    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }

    WSACleanup();
}

/**
 * Listens for incoming messages.
 */
void TCPSocket::listen() const {
    while (running) {
        char header[255];

        int result = recv(sock, header, sizeof(header), 0);

        if (result <= 0) {
            break;
        }

        unsigned char type = header[0];

        if (type == EFTSEND) {
            std::vector<unsigned char> pathBytes(header + 3, header + 3 + header[2]);
            std::string path(pathBytes.begin(), pathBytes.end());

            FileManager::writeFile(sock, path, header[1]);

            constexpr char buffer[255] = {
                0x6,
                0
            };

            send(sock, buffer, sizeof(buffer), 0);
        }

        else if (type == EFTINFO) {
            if (header[1] == DIR) {
                std::vector<unsigned char> pathBytes(header + 3, header + 3 + header[2]);
                std::string path(pathBytes.begin(), pathBytes.end());

                std::vector<std::string> files = FileManager::readDir(path);
            }
        }

        else if (type == EFTREAD) {
            std::vector<unsigned char> pathBytes(header + 2, header + 2 + header[1]);
            std::string path(pathBytes.begin(), pathBytes.end());

            std::vector<std::string> files = FileManager::readDir(path);

            std::string sizeString = std::to_string(files.size());

            send(sock, sizeString.c_str(), sizeString.size(), 0);

            recv(sock, header, sizeof(header), 0);

            for (const auto& file : files) {
                std::string delimited_file = file;

                if (file != files.back()) {
                    delimited_file += '\n';
                }

                send(sock, delimited_file.c_str(), delimited_file.size(), 0);
            }
        }
    }
}

/**
 * Stops to listen.
 */
void TCPSocket::stop() {
    running = false;
}