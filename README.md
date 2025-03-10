# WHATTHESHELL-A-Custom-Unix-Shell-Implementation

# Custom Shell (WHATTHESHELL)

This project is an implementation of a **Command Line Interface (CLI)** for the Advanced Operating Systems course (CSCI-P 536, Spring 2025). The shell supports file redirection, pipes, background execution, and error handling using system calls.

## Features
✔️ **Error handling**: Differentiates invalid commands  
✔️ **File redirection** (`<`, `>`)  
✔️ **Multiple pipes** (`|`)  
✔️ **Background process execution** (`&`)  
✔️ **System calls used**: `fork()`, `execvp()`, `pipe()`, `dup2()`, `wait()`, `open()`, `close()`

## Installation & Compilation
Clone the repository and use the Makefile to compile:
- cd os-lab-1-cli
- make

## Usage
Run the shell:
./myshell

## Design & Implementation
This shell follows the given grammar:
- command line: cmd [< fn] [| cmd]* [> fn] [&] EOL
- cmd: cn [ar]*
- cn: <string>   # Command name
- fn: <string>   # File name
- ar: <string>   # Argument
- &: Background execution


## Testing  
The shell was tested with various cases:  

- Basic Commands:`ls`, `pwd`, `echo "Hello"`  
- Redirection: `cat < input.txt > output.txt`  
- Pipes:`ls | grep .c | sort`  
- Background Execution:`sleep 10 &`  


