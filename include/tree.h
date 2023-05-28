#include <iostream>
#include <dirent.h>
#include <string>
using namespace std;

void print_directory_tree(string path, int level) {
    DIR* dir = opendir(path.c_str());
    if (dir == NULL) {
        cerr << "Error opening directory: " << path << endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string name = entry->d_name;
        if (name == "." || name == "..") {
            continue;
        }

        for (int i = 0; i < level; i++) {
            cout << "|   ";
        }
        cout << "|-- " << name << endl;

        if (entry->d_type == DT_DIR) {
            print_directory_tree(path + "/" + name, level + 1);
        }
    }

    closedir(dir);
}