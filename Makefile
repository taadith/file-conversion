CC := clang
CFlags := -g -Wall -Wextra

all-png: png test-png leaks-png

png: png.o
	$(CC) $(CFlags) png-file.o -o png-file

png.o: png/png_file.h png/png_file.c
	$(CC) $(CFlags) -c png/png_file.c -o png-file.o

test-png: test-png.o
	$(CC) $(CFlags) test-png-file.o -o test-png-file

test-png.o: png/png_file.h png/test_png_file.c
	$(CC) $(CFlags) -c png/png_file.h png/test_png_file.c

leaks-png: test-png-file
	leaks --atExit -- ./png-file images/dice.png
	leaks --atExit -- ./test-png-file

clear: png-file
	rm png-file
	rm *.o
	clear