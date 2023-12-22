#include <stdio.h>
#include <stdlib.h>

int main() {
    char * buffer = 0;
    int length = 0;
    FILE *f = fopen("./dice.png", "rb");
    if(f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
            fread(buffer, 1, length, f);
        fclose(f);
    }

    if(buffer) {
        printf("%.*s",length,buffer);
    }

    return 0;
}