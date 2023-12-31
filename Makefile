CC := clang
CFlags := -g -Wall -Wextra

all-png: png test-png leaks-png

png: png/png_file.h png/png_file.c
	$(CC) $(CFlags) png/png_file.c -o png-file

test-png: png/png_file.h png/test_png_file.c
	$(CC) $(CFlags) png/test_png_file.c -o test-png-file

leaks-png: test-png-file
	leaks --atExit -- ./test-png-file

clear: png
	rm png
	clear