# For each `.c` file in this sub-directory, _make_ each file before running the script

Each file can be run using the debugger as long as the `.vscode/tasks.json` is modified to run the needed arguments for each file. Please see below for details.

## Lab #1

Run `gcc -o scrabble scrabble.c -lm` prior to running the script: `./scrabble "<player1 word> <player2 word>"` where the words can be any combination of strings containing only alphabetical characters

## Problem #1 & #2

Run `gcc -o readability readability.c -lm` prior to running the script: `./readability "<insert your excerpt here>"` where an excerpt is as many sentences as the user desires

Run `gcc -o substitution substitution.c` prior to running the script: `./substitution <insert your key here> "<insert message here"` where a key is all 26 letters of the alphabet in any case, and message is any plain text message the user wants to encrypt
