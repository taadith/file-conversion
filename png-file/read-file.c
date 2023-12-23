#include <stdio.h>
#include <stdlib.h>

void file_length(FILE *fp, long *fl) {
    // moves file access position to EOF
    fseek(fp, 0L, SEEK_END);

    // ftell gives current access position
    *fl = ftell(fp);

    // could potentially use fseek?
    // fseek(fp, 0L, SEEK_SET);
    rewind(fp);
}

void print_file_header_contents(FILE *fp) {
    if (fp == NULL) {
        printf("error: file pointer is null\n");
        exit(1);
    }
    else {
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

        free(file_contents);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        FILE *fp = fopen("./dice.png", "rb");
        print_file_header_contents(fp);
        fclose(fp);
    }
    else if (argc == 2) {
        FILE *fp = fopen(argv[1], "rb");
        print_file_header_contents(fp);
        fclose(fp);
    }
    else {
        printf("error: invalid # of arguments passed to png-rf");
        exit(1);
    }

    return 0;
}