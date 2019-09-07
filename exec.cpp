#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <sys/wait.h>

#include "exec.h"
#include "piping.h"

using namespace std;


int execvString( const vector<string> &args ){
    char* c_arr[args.size()+1];

    for( unsigned int i=0; i<args.size(); i++){
        char* str = new char[(args[i]).size()+1];
        strcpy(str, (args[i]).c_str());
        c_arr[i] = str;
    }

    // Adding the null pointer to end of argument list to conform to execv
    c_arr[args.size()] = NULL;
    return execv(c_arr[0], c_arr);
}



void exec( const vector<string> &args){
    
    string filename = args[0];
    
    pid_t parentId = getpid();

    pid_t childId = fork();

    if(childId == 0){
        execvString(args);

        //TODO FIX THIS!
        if( errno ){
            stringstream ss;
            ss << "/bin/" << filename;
            string binName = ss.str();
            execvString(args);
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




void execute(const vector<string> &args){

    if( isPipeCommand(args) ){
        cout<<"Is pipe command"<<endl;
        const vector<string> *commands = splitPipeCommand(args);

         cout<<"Command 1: ";
        for( vector<string>::const_iterator it = commands[0].begin(); it != commands[0].end(); it++){        
            cout<<*it<<" ";
        }
        cout<<endl;

        cout<<"Command 2: ";
        for( vector<string>::const_iterator it = commands[1].begin(); it != commands[1].end(); it++){        
            cout<<*it<<" ";
        }
        cout<<endl;
        
    }else{
        cout<<"Is not pipe command"<<endl;
    }
    // Else: It's not a pipe command


    //cout<< (*commands)[0] <<endl;

   
}

