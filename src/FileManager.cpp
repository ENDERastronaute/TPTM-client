//
// Created by ender on 04/09/2024.
//

#include "FileManager.h"

#include <iostream>

/**
* Listens for a file stream and writes it on the disc.
* @param sock the socket.
* @param path the path where the file will be written.
* @param total the total number of bytes that'll be sent through the stream
* @return 0 if it successfully wrote the file.
*/
int FileManager::writeFile(SOCKET sock, const std::string& path, int total) {
    std::ofstream outputFile(path, std::ios::binary);

    char buffer[4096] = {};

    if (!outputFile) {
        outputFile.close();
        return ERROR_CANTOPEN;
    }

    int bytesWritten = 0;

    while (bytesWritten < total) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        outputFile.write(buffer, bytesReceived);
        bytesWritten += bytesReceived;
    }

    outputFile.close();

    return NO_ERROR;
}

/**
 * Reads a directory and outputs the path of all it's content (non-recursive).
 * @param path The path of the directory to be read.
 * @return The files' path
 */
std::vector<std::string> FileManager::readDir(const std::string &path) {
    std::vector<std::string> files;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string path = entry.path().string();

        if (entry.is_directory()) {
            path += '\\';
        }

        files.push_back(path);
    }

    return files;
}
