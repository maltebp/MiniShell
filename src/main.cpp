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

#include "history.h"
#include "tree.h"
#include "diff.h"
#include "find.h"
#include "wc.h"
#include "password.h"
#include "grep.h"

#define PROMPT "MiniShell:"

using namespace std;


// Prints the help message
void help(){
    cout<<"\nMiniShell is a small application implementing basic functionality:\n"<<
            "  cd [DIR]             \t Change working directory. '..' goes one directory back, and 'cd' goes to home directory.\n"<<
            "  dir/pwd              \t Prints current working directory.\n"
            "  [FILE] [ARG1] ..     \t Executes selected file if it's executable, including the given arguments.\n"<<
            "  [FILE1] | [FILE2]    \t Pipes the output of file 1 into the output of filee 2.\n"<<
            "  tree [DIR]           \t Prints the directory tree of the given directory.\n"<<
            "  diff [FILE1] [FILE2] \t Compares the two given files.\n"<<
            "  find [DIR] [NAME] [TYPE] [SIZE] \t Finds files in the given directory with the given name, type and size.\n"<<
            "  wc [FILE]            \t Prints the number of characters, words and lines in the given file.\n"<<
            "  grep [PATTERN] [FILE] \t Prints the lines in the given file that contain the given pattern.\n"<<
            "  history              \t Prints the history of commands.\n"<<
            "  password [LENGTH] [OPTIONS {-u: uppercase, -l: lowercase, -d: digits, -s: special characters}] \t Generates a random password.\n"<<
            endl;
}


/*  Prints the prompt message (MiniShell:WORKING_DIR$).
    It also uses the system call 'getcwd()' to get the
    current working dir. */
static void printPrompt(){
    char * dir = getcwd(NULL,0);
    if( dir == NULL ){
        cout<<"Error while printing working dir: "<<strerror(errno)<<endl;
        cout<<"\033[93m"<<PROMPT<<"$ ";
    } else {
        cout<<"\033[93m"<<PROMPT<<"\033[96m"<<dir<<"\033[37m$ ";
    }
}


/** Prints prompt message and reads the input of the user
 *  It returns the number of arguments (including command)
 *  givne by the user */
static int getInput(  vector<string> &args ){
    
    printPrompt();
    args.clear();

    string input;

    // Read entire line
    getline(cin, input);

    // Split line into arguments seperated by ' '
    stringstream ss(input);

    while( getline(ss, input, ' ')){
        args.push_back(input);
    }
    return args.size();
}


int main(){
    
    cout<< "\n\033[93mMiniShell started!\n\033[37m"<<endl;
    // type in green color
    cout<<"\033[92mType 'help' to see available functionality\nType 'history' to see history of your commands\n\n\033[37m";
    
    // Loop continues until the program is terminated externally (i.e. CTRL+C);

    while(1){
        vector<string> args;
        if( getInput(args) ){
            // Add the command to history
            add_command_to_history(args[0]);

            // Check if the command is "history"
            if (args[0] == "history") {
                print_command_history();
            }

            else{

            if( args[0] == "help") 
                help();

            // Check if its a tree command
            else if (args[0] == "tree") {
                string path = ".";
                if (args.size() > 1) {
                    path = args[1];
                }
                cout << path << endl;
                print_directory_tree(path, 0);
            }

            // Check if its a diff command
            else if (args[0] == "diff") {
                if (args.size() < 3) {
                    cout << "Usage: diff [FILE1] [FILE2]" << endl;
                } else {
                    compare_files(args[1], args[2]);
                }
            }

            // Check if its a find command
            else if (args[0] == "find"){
                string path = ".";
                string name = "";
                string type = "";
                long size = -1;
                if (args.size() > 1) {
                    path = args[1];
                }
                if (args.size() > 2) {
                    name = args[2];
                }
                if (args.size() > 3) {
                    type = args[3];
                }
                if (args.size() > 4) {
                    size = stol(args[4]);
                }
                find_files(path, name, type, size);
            }

            // Check if its wc command
            else if (args[0] == "wc") {
                if (args.size() < 2) {
                    cout << "Usage: wc [FILE]" << endl;
                } else {
                    string filename = args[1];
                    ifstream input_file(filename);
                    if (!input_file) {
                        cerr << "Error opening file: " << filename << endl;
                    }
                    string input((istreambuf_iterator<char>(input_file)), (istreambuf_iterator<char>()));
                    input_file.close();
                    cout << "Characters: " << count_chars(input) << endl;
                    cout << "Words: " << count_words(input) << endl;
                    cout << "Lines: " << count_lines(input) << endl;
                }
            }

            // Check if its a password command
            else if (args[0] == "password") {
                if (args.size() < 2) {
                    cout << "Usage: password [LENGTH] [optional -u -l -d -s]" << endl;
                } else {
                    int length = stoi(args[1]);
                    bool upper = false;
                    bool lower = true;
                    bool digit = false;
                    bool special = false;
                    if (args.size() > 2) {
                        for (int i = 2; i < args.size(); i++) {
                            if (args[i] == "-u") {
                                upper = true;
                            } else if (args[i] == "-l") {
                                lower = true;
                            } else if (args[i] == "-d") {
                                digit = true;
                            } else if (args[i] == "-s") {
                                special = true;
                            }
                        }
                    }
                    cout << generatePassword(length, upper, lower, digit, special) << endl;
                }
            }

            // Check if its a grep command
            else if (args[0] == "grep") {
                if (args.size() < 3) {
                    cout << "Usage: grep [PATTERN] [FILE]" << endl;
                } else {
                    string pattern = args[1];
                    string filename = args[2];
                    
                    grep(pattern, filename);
                }
            }

            // Check if its a dir command
            else if( !runDirCommand(args) ){
                
                // Check if its a pipe command
                if( isPipeCommand(args) )
                    forkCommandPipe(args);
                    
                // Single command
                else
                    forkCommandSingle(args);
            }

            }

        }
    }
    return 0;
}
