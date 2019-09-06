#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <sys/wait.h>

#include "exec.h"

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
    
    
    pid_t parentId = getpid();

    pid_t childId = fork();

    if(childId == 0){
        execvString(filename, args);

        if( errno ){
            stringstream ss;
            ss << "/bin/" << filename;
            string binName = ss.str();
            if(execvString(binName, args)) true;
        }

        /* Since execv will "ignore" remaining code if it's succesful,
            we can safely assume that an error has occured if we reach
            this point  */
        string errormsg(strerror(errno));
        cout<<"Error running program: "<<errormsg<<endl;
        
    }else if(childId > 0){
        int status;
        wait(&status);
    }else{
        cout<<"Error occured in forking process"<<endl;
    }
    
}


