# For each `.c` file in this sub-directory, _make_ each file before running the script

Each file can be run using the debugger as long as the `.vscode/tasks.json` is modified to run the needed arguments for each file. Each file's usage will be printed to console if incorrect arguments are supplied by the user.

# Problem #1

The Makefile will generate all the correct binaries and links for you using gcc. After running `rm -rf dictionary.o speller speller.o && make speller`, you can run `./speller <dictionary> <text file>` where dictionary is either `small` or `large` and text file is the file of text you would like to run a spell check on.
