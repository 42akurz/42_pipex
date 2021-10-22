# pipex - 42 School Project

[![akurz's 42Project Score](https://badge42.herokuapp.com/api/project/akurz/pipex)](https://github.com/JaeSeoKim/badge42)

## About

**Objectives**
* The goal of the pipex project is to recreate the behaviour 'pipe' operator ( | ) in C. To achieve this you are required to fork and work with multiple processes.  
* The 'pipe' is used for interprocess communication.    
* Your objective is to code the Pipex program.  
It should be executed in this way:
```bash
./pipex infile cmd1 cmd2 outfile
```
* Just in case: file1 and file2 are file names, cmd1 and cmd2 are shell commands with their parameters.  
The execution of the pipex program should do the same as the next shell command:
```bash
< infile cmd1 | cmd2 > outfile
```

**Examples**
```bash
 ./pipex infile "grep hello" "wc -w" outfile
 ```
 should be the same as
 ```bash
 < infile grep hello | wc -w > outfile
 ```
 
 **Explanation**  
 * The pipex program takes the content of a file descriptor ("infile").
 * The given commands will be executed in order on the infile's content.
 * The result will be written into the outfile. If the outfile doesn't exist yet, it will be created. Otherwise the previous content will be overwritten.
 
 ## Allowed functions

* access
* open
* unlink
* close
* read
* write
* malloc
* waitpid
* wait
* free
* pipe
* dup
* dup2
* execve
* fork
* perror
* strerror
* exit

## Approach
1. Creating a child process by "forking".
2. The child process is responsible for the execution of a given command and then redirecting the output into the "write end" of the "pipe".
3. After the child finished executing, the parent process will redirect the output of the previous child process ("write end" of the pipe) to be the 
input for the next child process ("read end" of the pipe).
4. The previous steps will be repeated for every given command.

## How to use

Clone the repository:
```bash
https://github.com/42akurz/42_pipex.git
```
Go to the repository and run make
```bash
make
```
Call the program like this (multiple commands possible)
```bash
./pipex infile cmd1 cmd2 outfile
```
Use clean to delete all object files, fclean to remove all object files and executable and re to recompile the program
```bash
make clean / make fclean / make re
```

 
