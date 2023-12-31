#ifndef PNG_FILE_H
#define PNG_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// table of CRC's of all 8-bit messages
unsigned long crc_table[256];

// flag: has the table been computed? Initially false
int crc_table_computed = 0;

// make the table for a fast CRC
void make_crc_table() {
    unsigned long c;
    for(int i = 0; i < 256; i++) {
        c = (unsigned long) i;
        for(int j = 0; j < 8; j++) {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[i] = c;
    }
    crc_table_computed = 1;
}

void clear_crc_table() {
    make_crc_table();
}

/* update a running CRC with the bytes buf[0..len-1]
   the CRC should be initialized to all 1's, 
   and the transmitted value is the 1's complement of the final running CRC 
   (see the crc() routine below). 
*/
unsigned long update_crc(unsigned long crc, unsigned char *buf, int len) {
    unsigned long c = crc;
    if(!crc_table_computed)
        make_crc_table();
    for(int i = 0; i < len; i++)
        c = crc_table[(c ^ buf[i]) & 0xff] ^ (c >> 8);
    return c;
}

// return the CRC of the bytes buf[0..len-1]
unsigned long crc(unsigned char *buf, int len)
{
  return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}

struct png_file {
    FILE *file_ptr;
    char *file_name;
    long *file_size;
    unsigned char *file_contents;
};

typedef struct png_file png_file;

//png signature never changes
unsigned char PNG_SIGNATURE[] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1a, '\n'};

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