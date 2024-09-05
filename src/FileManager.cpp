//
// Created by ender on 04/09/2024.
//

#include "FileManager.h"

#include <iostream>

int FileManager::writeFile(SOCKET sock, const std::string& path, int total) {

    std::cout << path << std::endl;
    std::ofstream outputFile(path, std::ios::binary);

    char buffer[4096] = {};
    int bytesReceived;

    if (!outputFile) {
        std::cout << "erreur fichier";
        return ERROR_CANTOPEN;
    }

    int bytesWritten = 0;

    while ((bytesReceived = recv(sock, buffer, sizeof(buffer), 0)) > 0 || bytesWritten < total) {
        outputFile.write(buffer, bytesReceived);
        bytesWritten += bytesReceived;
    }

    outputFile.close();

    return NO_ERROR;
}

