#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct def:
struct png_file {
    FILE *file_ptr;
    char* file_name;
    long *file_size;
    unsigned char *file_contents;
};

typedef struct png_file png_file;

// helper functions:
void compute_file_size(FILE*,long*);

// constructor:
png_file* create_png_file(char*);

// grabbing info:
