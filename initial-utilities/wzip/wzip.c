#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if we have at least one file
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    
    int current_char = -1;
    int count = 0;
    
    // Process each file
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        
        int c;
        while ((c = fgetc(fp)) != EOF) {
            if (c == current_char) {
                count++;
            } else {
                // Write out the previous run if it exists
                if (current_char != -1) {
                    fwrite(&count, sizeof(int), 1, stdout);
                    fputc(current_char, stdout);
                }
                current_char = c;
                count = 1;
            }
        }
        
        fclose(fp);
    }
    
    // Write out the last run if it exists
    if (current_char != -1) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(current_char, stdout);
    }
    
    return 0;
}
