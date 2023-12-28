#include "png_file.h"

int check_png_file(png_file *pf) {
    // checking filename

    // checking file signature
    if (memcmp(pf -> file_contents, PNG_SIGNATURE, 8) != 0)
        return 1;
    return 0;
}

//adding png_file to pfs
void add_png_file(png_file *pf) {
    if (pfs_capacity == 0) {
        pfs = (png_file**) malloc(sizeof(png_file*));
        pfs_capacity = 1;
    }
    else if (pfs_size + 1 > pfs_capacity) {
        //++pfs_size;
        //pfs_capacity *= 2;
        png_file **new_pfs = (png_file**) malloc(2 * pfs_capacity * sizeof(png_file*));
        for(unsigned int i = 0; i < pfs_size; i++)
            new_pfs[i] = pfs[i];
        free(pfs);
        pfs = new_pfs;
        pfs_capacity *= 2;
    }
    ++pfs_size;
    pfs[pfs_size - 1] = pf;
}

// struct constructor:
png_file* create_png_file(char* fn) {
    if (fn == NULL) {
        printf("error: NULL value provided as file name in char* variable\n");
        return NULL;
    }
    
    FILE *fp = fopen(fn, "rb");
    if(fp == NULL) {
        printf("error: file pointer is null\n");
        return NULL;
    }
    
    png_file *new_file = (png_file*) malloc(sizeof(png_file));
    if(new_file == NULL) {
        printf("error: png_file pointer is null");
        fclose(fp);
        return NULL;
    }

    // grabbing file_name and file_ptr
    new_file -> file_name = fn;
    new_file -> file_ptr = fp;
    
    // grabbing file_size
    fseek(fp, 0L, SEEK_END);        // moves file access position to EOF
    long fs = ftell(fp);            // ftell gives current access position
    new_file -> file_size = &fs; 
    rewind(fp);                     // could use fseek(fp, 0L, SEEK_SET);

    //grabbing file_contents
    new_file -> file_contents = malloc(*(new_file -> file_size));
    fread(new_file -> file_contents, *(new_file -> file_size), 1, fp);

    if (check_png_file(new_file) == 1) {
        printf("error: %s's PNG signature is incorrect\n", fn);
        fclose(fp);
        return NULL;
    }

    add_png_file(new_file);

    return new_file;
}

// png_file "destructor"
void free_png_file(png_file *pf) {
    // closing the file!
    if (fclose(pf -> file_ptr) != 0) {
        printf("error: png file not closed properly\n");
        exit(1);
    }

    // freeing file_contents ptr
    free(pf -> file_contents);
    pf -> file_contents = NULL;
    free(pf);
}

// pfs "destructor"
void free_png_files() {
    for(unsigned int i = 0; i < pfs_size; i++) {
        png_file *pf = pfs[i];
        free_png_file(pf);
        pf = NULL;
    }
    free(pfs);
    pfs = NULL;
    pfs_size = 0;
    pfs_capacity = 0;
}

unsigned char* print_png_chunk_information(unsigned char *chunk_start) {
    unsigned int chunk_data_length = 0, chunk_length = 12;
    char chunk_type[5]; chunk_type[4] = '\0';
    
    for(int i = 0; i < 4; i++)
        chunk_data_length += chunk_start[i] << (8 * (3 - i));
    chunk_length += chunk_data_length;
    
    
    strncpy(chunk_type, (const char *)(chunk_start + 4), 4);
    char ancillary = (chunk_type[0] >> 4) & 1;
    char private = (chunk_type[1] >> 4) & 1;
    char reserved = (chunk_type[2] >> 4) & 1;
    // char safe_to_copy = (chunk_type[3] >> 4) & 1;

    printf("Chunk Type: %s\n", chunk_type);
    if(ancillary)
        printf("    - Ancillary, not necessary for displaying image\n");
    else
        printf("    - Critical, necessary to displaying image\n");
    if(private)
        printf("    - Private, application-specific chunk\n");
    else
        printf("    - Public, part of PNG specs\n");
    if(reserved)
        printf("    - Unreserved, unknown chunk type\n");
    printf("Total Length of Chunk: %d\n", chunk_length);
    printf("Length of Data: %d\n", chunk_data_length);

    if(strcmp(chunk_type, "IEND"))
        return chunk_start + chunk_length;

    else
        return NULL;
}

void print_png_file_information(png_file *pf) {
    // checking if ptr is null
    if (pf == NULL) {
        printf("error: png_file ptr is null\n");
        exit(1);
    }
    else {
        printf("File Name: %s\n", pf -> file_name);
        printf("File Size: %ld bytes\n", *(pf -> file_size));

        

        unsigned int width = 0, height = 0;
        for(int i = 16; i < 20; i++)
            width += (pf -> file_contents[i]) << (8 * (19 - i));
        for(int i = 20; i < 24; i++)
            height += (pf -> file_contents[i]) << (8 * (19 - i));

        int bit_depth = 0, color_type = 0;
        int compression_method = 0, filter_method = 0, interlace_method = 0;
        bit_depth = pf -> file_contents[24];
        color_type = pf -> file_contents[25];
        compression_method = pf -> file_contents[26];
        filter_method = pf -> file_contents[27];
        interlace_method = pf -> file_contents[28];

        printf("Width: %d\n", width);
        printf("Height: %d\n", height);
        printf("Bit Depth: %d, number of bits per palette index\n", bit_depth);
        printf("Color Type: %d, ", color_type);
        if(color_type == 0)
            printf("each pixel is a grayscale sample\n");
        if(color_type == 2)
            printf("each pixel is an RGB triple\n");
        if(color_type == 3)
            printf("each pixel is a palette index (a PLTE chunk must appear)\n");
        if(color_type == 4)
            printf("each pixel is a grayscale sample and includes an alpha sample\n");
        if(color_type == 6)
            printf("each pixel is an RGB triple and includes an alpha sample\n");
        
        printf("Compression Method: %d, value indicates the method used to compress image data\n", compression_method);
        printf("Filter Method: %d, value indicates preprocessing method applied to image data before compression\n", filter_method);
        printf("Interlace Method: %d, value determines the transmission order of the image data\n", interlace_method);

        printf("File's Chunk Contents:\n");
        int chunk_no = 1;
        unsigned char* chunk_ptr = (pf -> file_contents) + 8;
        while(chunk_ptr != NULL) {
            printf("(%d)\n", chunk_no);
            chunk_ptr = print_png_chunk_information(chunk_ptr);
            chunk_no++;
        }
        printf("Total Number of Chunks: %d\n", chunk_no);
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        png_file* pf = create_png_file(argv[1]);
        if(pf == NULL) {
            exit(1);
        }
        
        print_png_file_information(pf);

        free_png_files();
    }
    else {
        perror("error: invalid # of arguments passed to png-rf\n");
        return (1);
    }

    return 0;
}