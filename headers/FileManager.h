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
    static int writeFile(SOCKET, const std::string&, uint64_t);
    static uint64_t convertToUInt64(uint8_t (&buffer)[8]);
    static std::string getFileName(const std::string&);

private:
    static std::regex buildRegex(const std::string&);
};



#endif //FILEMANAGER_H
