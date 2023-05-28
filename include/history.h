#pragma once

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> command_history;

void add_command_to_history(string command) {
    // add to hidden log file
    ofstream log_file;
    log_file.open("log.txt", ios::app);
    log_file << command << endl;
    log_file.close();
}

void print_command_history() {
    // read from log file
    ifstream log_file;
    log_file.open("log.txt");
    string command;
    while (getline(log_file, command)) {
        cout << command << endl;
    }
    log_file.close();
}