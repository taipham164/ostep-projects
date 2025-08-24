#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if we have at least the search term
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    
    char *searchterm = argv[1];
    
    // If no files are specified, read from standard input
    if (argc == 2) {
        char *line = NULL;
        size_t linecap = 0;
        ssize_t linelen;
        
        while ((linelen = getline(&line, &linecap, stdin)) > 0) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
        return 0;
    }
    
    // Process each file
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        
        char *line = NULL;
        size_t linecap = 0;
        ssize_t linelen;
        
        while ((linelen = getline(&line, &linecap, fp)) > 0) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
        
        free(line);
        fclose(fp);
    }
    
    return 0;
}
