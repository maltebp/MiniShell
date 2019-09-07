
#include "piping.h"


int isPipeCommand( const vector<string> &args ){
    for(int i=0; i<args.size(); i++){
        if( args[i] == "|" && i>0 && i<args.size()-1 ) return 1;
    }
    return 0;
}


int getPipeIndex(const vector<string> &args){
    for(int i=0; i<args.size(); i++){
        if( args[i] == "|" ) return i;
    }
    return -1;
}


const vector<string>* splitPipeCommand(const vector<string> &args){

    if(!isPipeCommand) return NULL;
    
    int pipeIndex = getPipeIndex(args);

    vector<string> *cmds;
    cmds = new vector<string>[2];   

    for( int i=0; i<pipeIndex; i++){
        cmds[0].push_back(args[i]);
    }

    for( int i=pipeIndex+1; i<args.size(); i++){
        cmds[1].push_back(args[i]);
    }

    return cmds;
}


// void testPipeCmd(){

//     vector<string> args;
//     args.push_back("cmd1");
//     args.push_back("arg1")
//     args.push_back("arg2")
//     args.push_back("|")
//     args.push_back("cmd2")
//     args.push_back("arg1")
//     args.push_back("arg2")


//     cout<<"Is "<<(isPipeCommand(args) ? "" : "not ")<<"pipe command"<<endl;

//     command cmds[2] = splitPipeCmd(args);

//     vector<string> *args = &(cmds[0].args);

//     for( int=0; i<args.size(); i++)

//     cout<<"Command 1:"
// }
