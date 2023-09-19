# Pipex

## Overview

Pipex reproduces the behavior of the shell pipe command in C.

## Usage

To use Pipex, follow these steps:

1. Clone the repository:

   git clone https://github.com/gkrusta/pipex.git

2. Compile the program:

make

3. Create an infile (if you want) and run the program with the desired commands:

./pipex infile "cmd1" "cmd2" outfile

- infile: The input file from which data is read.
- cmd1: The first command to be executed. Its output is piped to cmd2.
- cmd2: The second command to be executed.
- outfile: The output file where the final result is written.

## Bonus Features
Pipex also provides additional features, including:

### Managing multiple pipes:
$> ./pipex file1 "cmd1" "cmd2" "cmd3" ... "cmdN" file2

This command processes data from file1 through multiple commands (cmd1, cmd2, cmd3, ..., cmdN) and writes the final result to file2.
It behaves similarly to a chain of shell commands separated by pipes.

### Accepting << and >> when the first parameter is "here_doc":

$> ./pipex here_doc DELIMITER "cmd" "cmd1" outfile

This command processes input data by accepting lines until the DELIMITER is encountered.
It then pipes the output of cmd and cmd1 to outfile. This mimics the behavior of shell "here documents."

## Stuff and sources I used

- Behavior of pipes, forks, dup2 and execve funcitons:
  https://www.rozmichelle.com/pipes-forks-dups/
  
- This tutorial mainipulates each command in seperate childd process (the example I followed):
  https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901
  
- This processes the first command in child process and continues with the second command in the parent process, creating fork just once:
  https://dev.to/herbievine/42-a-comprehensive-guide-to-pipex-5165
