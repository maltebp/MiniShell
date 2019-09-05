#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <limits>
#include "exec.cpp"

using namespace std;

#define PROMPT "MiniShell$ "


vector<string> arguments;

bool run = true;


string readInput(){
    string input;
    do{
        cout<<PROMPT;
        getline(cin, input);
    }while(input.empty());
    return input;
}


void output(string msg){
    cout<<msg<<endl;
}

// Sort arguments and put them into vector (list)
int setArguments(string input){
    arguments.clear();
    string arg = "";
    for( string::iterator it = input.begin(); it != input.end(); it++){
        if( *it == ' '){
            if( !arg.empty() ) arguments.push_back(arg);
            arg.clear();
        }else{
            arg += *it;
        }
    }
    if( !arg.empty() ) arguments.push_back(arg);
    return arguments.size();
}


void printArgs(string input){
    cout<<"Arguments: ";
    for( vector<string>::iterator it=arguments.begin(); it!=arguments.end(); it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}



void evaluateInput(){
    string command = arguments.at(0);

    if( command == "exit")
        run = false;
    else if( command == "run"){
        arguments.erase(arguments.begin());
        exec(arguments.at(0), arguments);       
    }else
        output("Unrecognized command: "+command);
}



int main(){
    while(run){ 
        string input = readInput();
        if( setArguments(input) ){
            evaluateInput();
        };        
    }
    output("Goodbye!");
    return 0;
}
