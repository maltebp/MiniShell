#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void grep(const string &pattern, const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    int lineNumber = 1;

    while (getline(file, line))
    {
        size_t found = line.find(pattern);
        if (found != string::npos)
        {
            cout << lineNumber << ": " << line << endl;
        }

        lineNumber++;
    }

    file.close();
}