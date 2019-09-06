#ifndef EXEC_H
#define EXEC_H

#include <vector>
#include <string>

using namespace std;

int execvString( const string &path, const vector<string> &args);
void exec( string filename, const vector<string> &args);

#endif