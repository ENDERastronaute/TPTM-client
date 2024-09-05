//
// Created by ender on 04/09/2024.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <winsock2.h>
#include <fstream>

class FileManager {
public:
    static std::vector<std::string> readDir(const std::string&path);
    static int writeFile(SOCKET, const std::string&, int);
    static int writeMultipleFiles(SOCKET);
};



#endif //FILEMANAGER_H
