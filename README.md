# CS100 Assignment 2: Fall 2018

## Authors:
Steven Tran (https://github.com/azenros),
Ted Kim (https://github.com/tedminkim)

## Permanent Repo Link
https://github.com/cs100/assignment-1-spoopy-skeleton

## Introduction
This project `rShell` is a prototype shell designed to emulate a terminal and scripted to take an input and run commands based on the input given.

Command Syntax:
```
$ executable [flags] [connectors]
```

Available connecters are `||`, `&&`, `;`, and `#`
Decriptions:
   - `||` will run the command to the right of it only if the command to the left returns false or does not run
   - `&&` will run the command to the right of it only if the command to the left returns true or runs properly
   - `;` will run the command to the right of it regardless of the result of the commands before it
   - `#` denote comments and will ignore all text inputted after it

## Running rShell
To run rShell, open a terminal and run the following commands:
```
    1. Type "git clone https://github.com/cs100/assignment-1-spoopy-skeleton" into the terminal
    2. Move into the repository directory ("cd assignment-1-spoopy-skeleton/src")
    3. Create the output file ("g++ main.cpp rshell.cpp commands.cpp execute.cpp connector.cpp -std=c++11")
    4. Run the output file ("./a.out")
```

## Bugs
    1. If there are more than two commands inputted at the same time, only the last two commands will run (e.g. "mkdir test || ls -l && echo hello; ls -a" == "echo hello; ls -a"
    2. If 'exit' is not the first (and only) command in the line, it will not run.
