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

int main() {
    unsigned char *file_contents = NULL;
    FILE *fp = fopen("./dice.png", "rb");
    long fl = 0;
    if(fp != NULL) {
        file_length(fp,&fl);
        printf("File Size: %ld bytes\n", fl);

        file_contents = malloc(fl);
        fread(file_contents,fl,1,fp);
        printf("File Contents: ");
        for(int i = 12; i < 16; i++) {
            // // decimal representation
            // printf("%u ", file_contents[i]);

            // hexadecimal representation
            printf("%X ", file_contents[i]);

            // // char representation
            // printf("%c ", file_contents[i]);
        }
            
        printf("\n");
    }
    free(file_contents);
    fclose(fp);

    return 0;
}