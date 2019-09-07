#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <limits>
#include "exec.h"

using namespace std;

#define PROMPT "MiniShell$ "

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


// TEST METHOD
// void printArgs(string input, const vector<string> &args){
//     cout<<"Arguments: ";
//     for( vector<string>::iterator it=args.begin(); it!=args.end(); it++){
//         cout<<*it<<" ";
//     }
//     cout<<endl;
// }

string readInput(){
    string input;
    do{
        cout<<PROMPT;
        getline(cin, input);
    }while(input.empty());
    return input;
}

int main(){
    while(1){ 
        string input = readInput();
        const vector<string> args = getArguments(input);
        if(args.size()) exec(args);
    }
    return 0;
}
