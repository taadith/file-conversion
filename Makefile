CC := clang
CFlags := -Wall -Wextra

all: png-read-file

png-read-file: png-file/read-file.c
	$(CC) $(CFlags) png-file/read-file.c -o png-rf

clear: png-rf
	rm png-rf