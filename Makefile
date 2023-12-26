CC := clang
CFlags := -g -Wall -Wextra

all: png-file debug-png-file

png-file: png/png-file.h png/png-file.c
	$(CC) $(CFlags) png/png-file.c -o png-file

debug-png-file: png dice.png
	leaks --atExit -- ./png-file dice.png

clear: png
	rm png
	clear