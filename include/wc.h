#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int count_lines(string input) {
    int count = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '\n') {
            count++;
        }
    }
    return count;
}

int count_words(string input) {
    int count = 0;
    bool in_word = false;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            count++;
        }
    }
    return count;
}

int count_chars(string input) {
    return input.length();
}