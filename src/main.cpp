#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <limits>
#include <sstream>


#include "exec.h"
#include "piping.h"
#include "directory.h"

using namespace std;

#define PROMPT "MiniShell:"


void help(){
    cout<<"\nMiniShell is a small application implementing basic functionality:\n"<<
            "  cd [DIR]             \t Change working directory. '..' goes one directory back, and 'cd' goes to home directory.\n"<<
            "  dir/pwd              \t Prints current working directory.\n"
            "  [FILE] [ARG1] ..     \t Executes selected file if it's executable, including the given arguments.\n"<<
            "  [FILE1] | [FILE2]    \t Pipes the output of file 1 into the output of filee 2.\n"<<
            endl;
}


static void printPrompt(){
    char * dir = getcwd(NULL,0);
    if( dir == NULL ){
        cout<<"Error while printing working dir: "<<strerror(errno)<<endl;
        cout<<"\033[93m"<<PROMPT<<"$ ";
    } else {
        cout<<"\033[93m"<<PROMPT<<"\033[96m"<<dir<<"\033[37m$ ";
    }
}


static int getInput(  vector<string> &args ){
    string input;

    printPrompt();

    args.clear();

    getline(cin, input);

    stringstream ss(input);

    while( getline(ss, input, ' ')){
        args.push_back(input);
    }
    return args.size();
}


int main(){
    
    cout<< "\n\033[93mMiniShell started! Type 'help' to see available functionality\033[37m"<<endl;;
    
    while(1){
        vector<string> args;
        if( getInput(args) ){
            if( args[0] == "help") 
                help();
            else if( !runDirCommand(args) ){
                
                if( isPipeCommand(args) )
                    forkCommandPipe(args);
                    
                else
                    forkCommandSingle(args);
            }
        }
    }
    return 0;
}
