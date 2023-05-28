#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool swapFiles(const string &file1, const string &file2)
{
    // Read file1
    ifstream input1(file1, ios::binary);
    if (!input1)
    {
        cerr << "Error opening file: " << file1 << endl;
        return false;
    }
    string contents1((istreambuf_iterator<char>(input1)), istreambuf_iterator<char>());
    input1.close();

    // Read file2
    ifstream input2(file2, ios::binary);
    if (!input2)
    {
        cerr << "Error opening file: " << file2 << endl;
        return false;
    }
    string contents2((istreambuf_iterator<char>(input2)), istreambuf_iterator<char>());
    input2.close();

    // Swap the contents
    swap(contents1, contents2);

    // Write the swapped contents back to the files
    ofstream output1(file1, ios::binary | ios::trunc);
    if (!output1)
    {
        cerr << "Error opening file: " << file1 << endl;
        return false;
    }
    output1.write(contents1.c_str(), contents1.size());
    output1.close();

    ofstream output2(file2, ios::binary | ios::trunc);
    if (!output2)
    {
        cerr << "Error opening file: " << file2 << endl;
        return false;
    }
    output2.write(contents2.c_str(), contents2.size());
    output2.close();

    cout << "Contents swapped successfully." << endl;
    return true;
}