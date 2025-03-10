# WHATTHESHELL-A-Custom-Unix-Shell-Implementation
## Introduction
This project is an implementation of a **Command Line Interface (CLI)** for the Advanced Operating Systems course (CSCI-P 536, Spring 2025). The shell supports file redirection, pipes, background execution, and error handling using system calls.

## Purpose
The purpose of this project is to gain a concrete understanding of how command-line interfaces (CLIs) work by implementing:
- Command parsing and execution.
- Handling multiple parameters and various operators.
- Utilizing system calls such as `fork()`, `wait()`, `execvp()`, `open()`, `close()`, `dup()`, `dup2()`, and `pipe()`.

## Features
This shell supports the following functionalities:
- **Executing commands** (e.g., `ls`, `cat file.txt`).
- **Error handling** for invalid commands.
- **File redirection** using `<` (input) and `>` (output).
- **Piping (`|`)** to chain multiple commands.
- **Background execution (`&`)**.

## Installation & Setup
### Prerequisites
- **Linux/macOS** environment.
- **GCC compiler** installed.

### Compilation
To compile the shell, run:
```sh
make
```
### Running the Shell
To start the shell, execute:
```sh
./myshell
```

## Design & Implementation
This shell follows the given grammar:
- command line: cmd [< fn] [| cmd]* [> fn] [&] EOL
- cmd: cn [ar]*
- cn: <string>    # Command name
- fn: <string>    # File name
- ar: <string>    # Argument
- &: Background execution


## Testing  
The shell was tested with various cases:  

- Basic Commands:`ls`, `pwd`, `echo "Hello"`  
- Redirection: `cat < input.txt > output.txt`  
- Pipes:`ls | grep .c | sort`  
- Background Execution:`sleep 10 &`  


