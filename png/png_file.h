#ifndef PNG_FILE_H
#define PNG_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//png signature never changes
unsigned char PNG_SIGNATURE[] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};

// struct def:
struct png_file {
    FILE *file_ptr;
    char *file_name;
    long *file_size;
    unsigned char *file_contents;
};

typedef struct png_file png_file;

// need to implement some image representation for png_file to contain
// this image rep can then be passed on to the next struct! 
// end goal is some function like this - create_jpeg_file(png_file*)

// makes freeing all png_files easy when all stored in a dynamically allocated list
png_file **pfs = NULL;
unsigned int pfs_size = 0;
unsigned int pfs_capacity = 0;

// constructor:
png_file* create_png_file(char*);

// TODO: file checker
int check_png_file(png_file*);

// adding png_file to pfs
void add_png_file(png_file*);

// png_file "destructor":
void free_png_file(png_file*);

// pfs "destructor":
void free_png_files();

// TODO: grabbing info from chunk:
unsigned char* print_png_chunk_information(unsigned char *);

// TODO: grabbing file info
void print_png_file_information(png_file *);

#endif