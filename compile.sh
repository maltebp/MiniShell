#!/bin/bash
sudo rm -rf $HOME/MiniShell && cp -avr $WIN/MiniShell $HOME/MiniShell && cd $HOME/MiniShell && make clean && make && ./minishell && cd ..