CC := clang
CFlags := -g -Wall -Wextra

all-png: png debug-png

png: png/png_file.h png/png_file.c
	$(CC) $(CFlags) png/png_file.c -o png-file

debug-png: png-file dice.png
	leaks --atExit -- ./png-file dice.png

clear: png
	rm png
	clear