# MiniShell 
[![Build Status](https://travis-ci.org/maltebp/MiniShell.svg?branch=master)](https://travis-ci.org/maltebp/MiniShell)

A small shell application for a UNIX operating system written in __C++__, using UNIX system calls to provide basic bash-like shell functionality.

[Latest Release](http://github.com/maltebp/MiniShell/releases/latest)

This is a __school project__ for '62588 Operating Systems' at DTU, Denmark.

### Features
 - Change / list working directory
 - Running executable files, including passing arguments
 - Piping

### Install and Run
 1. Download source code/project from the [latest release link](http://github.com/maltebp/MiniShell/releases/latest) to a UNIX OS.
 2. Unpack project
 3. (Optional) Build by either:
    1. Set execute permission on _compile.sh_ in root folder with 'sudo chmod +x compile.sh' and run the script
    1. Run _makefile_ by typing in 'make' in terminal while in root folder
 4. Start application by running _bin/minishell_


__ATTENTION__

The project has been developed and tested __only__ on following specs:
 - OS: Windows Ubuntu Subsystem (Ubuntu v. 18.04)
 - Compiler: MinGW64 (g++) v. 7.4.0 
