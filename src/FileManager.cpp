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

        if (bytesReceived < 0) {
            throw std::exception();
        }

        outputFile.write(buffer, bytesReceived);
        bytesWritten += bytesReceived;
    }

    outputFile.close();

    return NO_ERROR;
}

/**
 * Reads a directory and outputs the path of all it's content (non-recursive).
 * @param path The path of the directory to be read.
 * @param filter The filter
 * @param nodir False you want to get directories, true if you do not. By default false.
 * @return The files' path
 */
std::vector<std::string> FileManager::readDir(const std::string &path, const std::string &filter, const bool nodir) {
    std::vector<std::string> files;

    const std::regex re = buildRegex(filter);

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::string p = entry.path().string();

        if (std::regex_match(p, re)) {
            if (nodir) {
                if (!entry.is_directory()) {
                    files.push_back(p);
                }
            }
            else {
                if (entry.is_directory()) {
                    p += '\\';
                }

                files.push_back(p);
            }
        }
    }

    return files;
}

std::regex FileManager::buildRegex(const std::string& string) {
    std::string regex_str = "(";

    for (const char &c : string) {
        if (c == ' ') {
            regex_str += ")";
            regex_str += "|";
            regex_str += "(";
        }
        else if (c == '*') {
            regex_str += ".*";
        }
        else if (c == '.') {
            regex_str += "\\.";
        }
        else if (c == '+') {
            regex_str += "\\+";
        }
        else {
            regex_str += c;
        }
    }
    regex_str += ")";

    return std::regex(regex_str, std::regex_constants::ECMAScript | std::regex_constants::icase);
}

std::string FileManager::getFileName(const std::string& path) {
    std::filesystem::path p(path);
    return p.filename().string();
}
