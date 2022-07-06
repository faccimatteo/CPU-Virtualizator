## CPU Virtualizator 

This C-project simulate the Assmebly language by using simple instructions written in a file.cvm and executing its content.

## Project files 

```
project
│   Makefile
│
└───include
│       execute.h
│       print.h
│       read.h
│
└───src
        esegui.c
        leggi.c
        stampa.c
        vm.c
```


## What do you need?

This project make use of the compiler gcc, so it is required before its usage.
To install gcc:

MacOS:
1. Install Homebrew by using the following<br> 
`$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
2. brew install gcc 

Linux:
`$ sudo apt-get install gcc`

Windows:
Install Cygwin from https://cygwin.com/

To correctly work, you must provide a correctly formatted .cvm file.

## How to write a .cvm file 
The file can contains all the following instructions and the number of lines must be specified as the first valid line.
Every instruction must end with a `;`.
You are allowed to insert comments after `;`.

The following is the list of command you can use to write a program. 

| Command name | Command number | First parameter   | Second parameter  | Description                                                                                                                                                                                                        |  
|--------------|----------------|-------------------|-------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|                                                                                                      
| HALT         | 0              |         -         |         -         | terminate program                                                                                                                                                                                                  |
| DISPLAY      | 1              | 0-31 (reg R0-R31) |         -         | print on stdout value of the registers (-1: all of them)                                                                                                                                                           |
| PRINT STACK  | 2              |       number      |         -         | print on stdout stack values                                                                                                                                                                                       |
| PUSH         | 10             | 0-31 (reg R0-R31) |         -         | insert on the stack the value of the registry defined by pos, and increment the stack pointer. Terminate if stack overflow                                                                                         |
| POP          | 11             | 0-31 (reg R0-R31) |         -         | copy the value taken from the stack (after the decreasing) in the registry. Terminates if stack underflow                                                                                                          |
| MOV          | 12             | 0-31 (reg R0-R31) |       number      | copy the value in the registry                                                                                                                                                                                     |
| CALL         | 20             |        pos        |         -         | substitute instruction pointer with value in pos                                                                                                                                                                   |
| RET          | 21             |         -         |         -         | execute a call to a subroutine. Terminate if stack overflow                                                                                                                                                        | 
| JMP          | 22             |        pos        |         -         | return from a subroutine. Terminate if stack underflow                                                                                                                                                             |
| JZ           | 23             |        pos        |         -         | substitute the value of the instruction pointer with the value in pos1 if the value of the registry in pos2 is 0                                                                                                   |
| JPOS         | 24             |        pos        |         -         | substitute the value of the instruction pointer with the value in pos1 if the value of the registry in pos2 is positive                                                                                            |
| JNEG         | 25             |        pos        |         -         | substitute the value of the instruction pointer with the value in pos1 if the value of the registry in pos2 is negative                                                                                            |
| ADD          | 30             | 0-31 (reg R0-R31) | 0-31 (reg R0-R31) | integer sum between registry value in pos1 and pos2. The result of the sum is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow                                             | 
| SUB          | 31             | 0-31 (reg R0-R31) | 0-31 (reg R0-R31) | integer subtraction between registry value in pos1 and pos2. The result of the subtraction is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow                             |
| MUL          | 32             | 0-31 (reg R0-R31) | 0-31 (reg R0-R31) | integer multiplication between registry value in pos1 and pos2. The result of the multiplication is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow                       |
| DIV          | 33             | 0-31 (reg R0-R31) | 0-31 (reg R0-R31) | integer division between registry value in pos1 and pos2. The result of the division is copied in the registry identified by pos3. Terminate if aritmethic overflow or underflow or registry in pos2 is equal to 0 |

## How to run the program? 

Place yourself into the root folder of the projet and execute make.
After then you can execute VM to perform the features below. 


## Features 

Once a file.cvm correctly formatted is created, you can:

* Execute the program by using  `VM execute filename.cvm`;
* Print the content of the file by using `VM print filename.cvm`.

