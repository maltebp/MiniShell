// touch.h
#ifndef TOUCH_H
#define TOUCH_H

#include <iostream>
#include <fstream>

void createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return;
    }

    file.close();
}

#endif

