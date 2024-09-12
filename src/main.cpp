#include "UDPSocket.h"
#include <thread>
#include <iostream>
#include "TCPSocket.h"

int main() {
    UDPSocket server_socket("0.0.0.0", 3000);

    std::thread listener(&UDPSocket::listen, &server_socket);

    while (server_socket.getRemoteIp().empty()) {}

    const TCPSocket client_socket("0.0.0.0", 8000);

    client_socket.connectToServer(server_socket.getRemoteIp(), 8000);

    client_socket.listen();
}
