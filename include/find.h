#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <vector>
using namespace std;

void find_files(string path, string name, string type, long size) {
    DIR* dir;
    struct dirent* entry;
    struct stat file_stat;
    vector<string> subdirs;
    
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            string filename = entry->d_name;
            if (filename == "." || filename == "..") {
                continue;
            }
            string full_path = path + "/" + filename;
            if (stat(full_path.c_str(), &file_stat) == -1) {
                cerr << "Error getting file information: " << full_path << endl;
                continue;
            }
            if (S_ISDIR(file_stat.st_mode)) {
                subdirs.push_back(full_path);
            } else if (S_ISREG(file_stat.st_mode)) {
                bool name_matches = (name.empty() || filename.find(name) != string::npos);
                bool type_matches = (type.empty() || filename.substr(filename.find_last_of(".") + 1) == type);
                bool size_matches = (size == -1 || file_stat.st_size == size);
                if (name_matches && type_matches && size_matches) {
                    cout << full_path << endl;
                }
            }
        }
        closedir(dir);
    } else {
        cerr << "Error opening directory: " << path << endl;
        return;
    }
    for (string subdir : subdirs) {
        find_files(subdir, name, type, size);
    }
}