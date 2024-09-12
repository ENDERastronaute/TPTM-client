//
// Created by ender on 04/09/2024.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <winsock2.h>
#include <fstream>
#include <regex>
#include <filesystem>

class FileManager {
public:
    static std::vector<std::string> readDir(const std::string&, const std::string& = "*", bool = false);
    static int writeFile(SOCKET, const std::string&, int);
    static int writeMultipleFiles(SOCKET);
    static int sendMultipleFiles(SOCKET);
    static std::string getFileName(const std::string&);

private:
    static std::regex buildRegex(const std::string&);
};



#endif //FILEMANAGER_H
