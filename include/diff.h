#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void compare_files(string filename1, string filename2) {
    ifstream file1(filename1);
    ifstream file2(filename2);

    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error opening files: " << filename1 << ", " << filename2 << endl;
        return;
    }

    string line1, line2;
    int line_num = 1;
    bool differences_found = false;

    while (getline(file1, line1) && getline(file2, line2)) {
        if (line1 != line2) {
            cout << "Line " << line_num << ":" << endl;
            cout << "[0] " << line1 << endl;
            cout << "[1] " << line2 << endl;
            differences_found = true;
        }
        line_num++;
    }

    if (!differences_found) {
        cout << "No differences found" << endl;
    }

    file1.close();
    file2.close();
}