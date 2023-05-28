// Implement the below functionality
// 1.	history: display a list of previously executed commands
// 2.	tree: display the directory structure of a file system as a tree diagram
// 3.	htop: an enhanced version of top with a more user-friendly interface and additional features
// 4.	awk: a powerful text processing tool for manipulating data in tabular format
// 5.	diff: compare the contents of two files or directories
// 6.	du: display disk usage information for files and directories
// 7.	df: display disk space information for file systems
// 8.	find: search for files and directories that match certain criteria (name, type, size, etc.)
// 9.	wc: count the number of lines, words, and characters in a text file or output stream
// 10.	head: display the first few lines of a text file or output stream
// 11.	tail: display the last few lines of a text file or output stream

#include "directory.h"
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <cstdlib>


// Prints working directory using system call getcwd
void printDirectory(){
    char * dir = getcwd(NULL,0); // Fetching pointer to str holding name
    if( dir == NULL ) cout<<"Error while printing working dir: "<<strerror(errno)<<endl;
    else cout<<dir<<endl;
}

/* Changes the directory to the given path.
     "cd .." works and using only 'cd' makes you go to $home */
void changeDirectory(string path){
    if(chdir(path.c_str()) == -1){
        cout<<"Error: "<<strerror(errno)<<endl;;
    }
}

/* Checks if a given command is a directory command (cd/pwd/dir), and in
    that case runs the appropriate functionality. */
int runDirCommand(const vector<string> &args){
    if( args[0] == "cd" ){
        if(args.size() > 2)
            cout<<"Too many arguments"<<endl;
        else{
            if(args.size() == 1) changeDirectory(getenv("HOME"));
            else changeDirectory(args[1]);
        }
        return 1;
    }
    if( args[0] == "pwd" || args[0] == "dir"){
        if(args.size() > 1 )
            cout<<"Too many arguments"<<endl;
        else{
            printDirectory();
        }
        return 1;
    }

    return 0;
}
