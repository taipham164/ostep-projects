#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Structure for storing lines in a linked list
typedef struct line_node {
    char *line;
    struct line_node *next;
} line_node_t;

// Function to add a line to the front of the linked list
line_node_t* add_line(line_node_t *head, char *line) {
    line_node_t *new_node = malloc(sizeof(line_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    
    // Duplicate the line
    new_node->line = malloc(strlen(line) + 1);
    if (new_node->line == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    strcpy(new_node->line, line);
    
    new_node->next = head;
    return new_node;
}

// Function to free the linked list
void free_list(line_node_t *head) {
    while (head != NULL) {
        line_node_t *temp = head;
        head = head->next;
        free(temp->line);
        free(temp);
    }
}

// Function to check if two files are the same
int files_are_same(const char *file1, const char *file2) {
    struct stat stat1, stat2;
    
    if (stat(file1, &stat1) != 0 || stat(file2, &stat2) != 0) {
        return 0; // If we can't stat either file, assume they're different
    }
    
    // Check if they're the same device and inode
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);
}

// Function to process input and reverse lines
void process_input(FILE *input, FILE *output) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    line_node_t *head = NULL;
    
    // Read all lines and store them in a linked list
    while ((nread = getline(&line, &len, input)) != -1) {
        head = add_line(head, line);
    }
    
    // Print lines in reverse order (head of list is last line read)
    line_node_t *current = head;
    while (current != NULL) {
        fprintf(output, "%s", current->line);
        current = current->next;
    }
    
    // Clean up
    free(line);
    free_list(head);
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;
    
    // Check for too many arguments
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    
    // Case 1: No arguments - read from stdin, write to stdout
    if (argc == 1) {
        process_input(stdin, stdout);
        return 0;
    }
    
    // Case 2: One argument - read from file, write to stdout
    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        process_input(input, stdout);
        fclose(input);
        return 0;
    }
    
    // Case 3: Two arguments - read from input file, write to output file
    if (argc == 3) {
        // Check if input and output files are the same
        if (files_are_same(argv[1], argv[2])) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
        
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            fclose(input);
            exit(1);
        }
        
        process_input(input, output);
        
        fclose(input);
        fclose(output);
        return 0;
    }
    
    return 0;
}
