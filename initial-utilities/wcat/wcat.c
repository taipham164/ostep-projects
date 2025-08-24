#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // If no files are specified, just exit with status 0
    if (argc == 1) {
        return 0;
    }
    
    // Process each file in order
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        
        // Read and print the file line by line
        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        
        fclose(fp);
    }
    
    return 0;
}
