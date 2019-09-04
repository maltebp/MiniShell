#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define PROMPT "MiniShell$ "

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


void handleInput(string input){

    
    if( input == "exit")
        run = false;
    else if( input == "hello"){
        string filename = "hello";
        char str[15];
        strcpy(str, filename.c_str() );
    
        char* const args[] = {str, NULL};
        cout<<"test..."<<endl;
        execv("/home/maltebp/hello", args);
        cout<<"Something went wrong: "<<errno<<endl;
    }
    else
        output(input);
}


void printArgs(string input){
    cout<<"Arguments: ";
    string s = "";
    for( string::size_type i=0; i<input.size(); i++){
        if( input[i] == ' '){
            cout<<"\""<<s<<"\" ";
            s = "";
        }else{
            s = s + input[i];
        }
    }
    cout<<endl;
}

int main(){
    while(run){
        string input = readInput();
        printArgs(input);
        handleInput(input);
    }

    output("Goodbye!");
    return 0;
}
