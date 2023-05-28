// ls.h
#ifndef LS_H
#define LS_H

#include <iostream>
#include <dirent.h>

void listDirectory(const std::string& path) {
    DIR* directory = opendir(path.c_str());
    if (directory == nullptr) {
        std::cerr << "Error opening directory: " << path << std::endl;
        return;
    }

    dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        std::cout << entry->d_name << std::endl;
    }

    closedir(directory);
}

#endif

