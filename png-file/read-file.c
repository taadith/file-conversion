#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned char *file_contents;
    FILE *fp = fopen("./dice.png", "rb");
    long file_size = 0;
    if(fp != NULL) {
        //moves file access position to EOF
        fseek(fp, 0L, SEEK_END);

        //ftell gives current access position
        file_size = ftell(fp);

        //could also use fseek(fp, 0L, SEEK_SET)
        rewind(fp);

        file_contents = malloc(file_size);
        fread(file_contents,file_size,1,fp);
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
    fclose(fp);

    printf("File Size: %ld bytes\n", file_size);
    return 0;
}