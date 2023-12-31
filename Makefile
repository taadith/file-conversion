CC := clang
CFlags := -g -Wall -Wextra

all-png: png leaks-png

png: png.o
	$(CC) $(CFlags) png-file.o -o png-file

png.o: png/png_file.h png/png_file.c
	$(CC) $(CFlags) -c png/png_file.c -o png-file.o

leaks-png: png-file
	leaks --atExit -- ./png-file

clear: png-file
	rm png-file
	rm *.o
	clear