# For each `.c` file in this sub-directory, _make_ each file before running the script

Each file can be run using the debugger as long as the `.vscode/tasks.json` is modified to run the needed arguments for each file. Please see below for details.

## Lab #1

Mainly an excercise to run sorting algorithms in named binaries against data sets to see what each binary's algorithm is.

## Problem #1

Due to the reliance of get_string and get_int, this application may not be able to be run on your local machine without `cs50.h`. If you have `cs50.h` you can run `gcc -o plurality plurality.c -lcs50` to run the script.
