#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_length(FILE *fp, long *fl) {
    // moves file access position to EOF
    fseek(fp, 0L, SEEK_END);

    // ftell gives current access position
    *fl = ftell(fp);

    // could potentially use fseek?
    // fseek(fp, 0L, SEEK_SET);
    rewind(fp);
}

void print_png_chunk_information(unsigned char *chunk_start) {
    int chunk_data_length = 0, chunk_length = 12;
    char chunk_type[5]; chunk_type[4] = '\0';
    
    for(int i = 0; i < 4; i++)
        chunk_data_length += chunk_start[i] << (8 * (3 - i));
    chunk_length += chunk_data_length;
    
    char ancillary, private, reserved, safe_to_copy;
    strncpy(chunk_type, (const char *)(chunk_start + 4), 4);
    
    
    printf("Chunk Type: %s\n", chunk_type);
    printf("Total Length of Chunk: %d\n", chunk_length);
    printf("Length of Data: %d\n", chunk_data_length);
}

void print_png_file_information(FILE *fp, char *filename) {
    if (fp == NULL) {
        perror("error: file pointer is null\n");
        return;
    }
    else {
        printf("File Name: %s\n", filename);
        long fl = 0;
        file_length(fp,&fl);
        printf("File Size: %ld bytes\n", fl);

        unsigned char *file_contents = malloc(fl);
        fread(file_contents, fl, 1, fp);

        unsigned int width = 0, height = 0;
        for(int i = 16; i < 20; i++)
            width += file_contents[i] << (8 * (19 - i));
        for(int i = 20; i < 24; i++)
            height += file_contents[i] << (8 * (19 - i));

        int bit_depth = 0, color_type = 0;
        int compression_method = 0, filter_method = 0, interlace_method = 0;
        bit_depth = file_contents[24];
        color_type = file_contents[25];
        compression_method = file_contents[26];
        filter_method = file_contents[27];
        interlace_method = file_contents[28];

        printf("Width: %d\n", width);
        printf("Height: %d\n", height);
        printf("Bit Depth: %d, number of bits per palette index\n", bit_depth);
        printf("Color Type: %d, value describes interpretation of image data\n", color_type);
        printf("Compression Method: %d, value indicates the method used to compress image data\n", compression_method);
        printf("Filter Method: %d, value indicates preprocessing method applied to image data before compression\n", filter_method);
        printf("Interlace Method: %d, value determines the transmission order of the image data\n", interlace_method);

        print_png_chunk_information(file_contents + 33);
        print_png_chunk_information(file_contents + 33 + 226888);

        free(file_contents);
    }
}



int main(int argc, char **argv) {
    if (argc == 2) {
        FILE *fp = fopen(argv[1], "rb");
        print_png_file_information(fp, argv[1]);
        fclose(fp);
    }
    else {
        perror("error: invalid # of arguments passed to png-rf");
        return (1);
    }

    return 0;
}