#include "UDPSocket.h"
#include <thread>
#include <iostream>
#include "TCPSocket.h"

int main() {
    while (true) {
        UDPSocket server_socket("0.0.0.0", 3000);
        TCPSocket client_socket("0.0.0.0", 4000);

        try {
            std::thread listener(&UDPSocket::listen, &server_socket);

            while (server_socket.getRemoteIp().empty()) {}

            server_socket.close();

            listener.join();

            client_socket.connectToServer(server_socket.getRemoteIp(), 8000);

            client_socket.listen();
        }
        catch (std::exception &e) {
            server_socket.close();
            client_socket.stop();
        }
    }
}
