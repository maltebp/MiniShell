#!/bin/bash
sudo rm -rf $HOME/MiniShell && cp -avr $WIN/MiniShell $HOME/MiniShell && cd $HOME/MiniShell && make clean && make && ./minishell && cd ..
# Removes the MiniShell directory from Ubuntu, copies the directory from Windows, runs the make cleaning and make, and runs the projects