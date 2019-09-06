
#include <iostream>
#include <vector>
#include "exec.h"
#include <unistd.h>
#include <sstream>
#include <cstring>


using namespace std;


int execvString( const string &path, const vector<string> &args){

    char* c_arr[args.size()+1];

    for( unsigned int i=0; i<args.size(); i++){
        char* str = new char[(args[i]).size()+1];
        strcpy(str, (args[i]).c_str());
        c_arr[i] = str;
    }

    // Adding the null pointer to end of argument list to conform to execv
    c_arr[args.size()] = NULL;

    return execv(path.c_str(), c_arr);
}


void exec( string filename, const vector<string> &args){
    
    
    cout<<"Exec "<<filename<<endl;

    int result = execvString(filename, args);

    cout<<"Execv Res: "<<result<<endl;

    string errormsg(strerror(errno));

    cout<<"Error running program: "<<errormsg<<endl;

    

    cout<<"Finished"<<endl;

    
}


