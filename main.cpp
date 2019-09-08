#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <limits>


#include "exec.h"
#include "piping.h"
#include "directory.h"

using namespace std;

#define PROMPT "MiniShell:"


// Sort arguments and put them into vector (list)
const vector<string>& getArguments(string input){
    vector<string> *args;
    args = new vector<string>;
    string arg = "";
    for( string::iterator it = input.begin(); it != input.end(); it++){
        if( *it == ' '){
            if( !arg.empty() ) (*args).push_back(arg);
            arg.clear();
        }else{
            arg += *it;
        }
    }
    if( !arg.empty() ) (*args).push_back(arg);
    return (*args);
}


// Reads user input from terminal (executable commands ls, cat, nano etc);
string readInput(){
    string input;
    do{
        
        char * dir = getcwd(NULL,0);
        if( dir == NULL ){
            cout<<"Error while printing working dir: "<<strerror(errno)<<endl;
            cout<<PROMPT<<"$ ";
        } else {
            cout<<PROMPT<<dir<<"$ ";
        }
        getline(cin, input);
    }while(input.empty());
    return input;
}



int main(){
    while(1){ 
        string input = readInput();
        const vector<string> args = getArguments(input);
        if(args.size() > 0){
            if( !runDirCommand(args) ){
                if( isPipeCommand(args) )
                    forkCommandPipe(args);
                    
                else
                    forkCommandSingle(args);
            }
        }
    }
    return 0;
}
