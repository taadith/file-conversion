#ifndef PNG_FILE_H
#define PNG_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct def:
struct png_file {
    FILE *file_ptr;
    char *file_name;
    long *file_size;
    unsigned char *file_contents;
};

typedef struct png_file png_file;

png_file **pfs = NULL;
unsigned int pfs_size = 0;
unsigned int pfs_capacity = 0;

// constructor:
png_file* create_png_file(char*);

//adding png_file to pfs
void add_png_file(png_file*);

// png_file "destructor":
void free_png_file(png_file*);

// pfs "destructor":
void free_png_files();

//grabbing info:
unsigned char* print_png_chunk_information(unsigned char *);
void print_png_file_information(png_file *);

#endif