#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void search_file(char mode, char* pattern, char* filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    char line[512];
    int line_num = 1;
    int occurrence_count = 0;
    int first_found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {
            occurrence_count++;
            if (mode == 'f' && !first_found) {
                printf("First occurrence at Line %d: %s", line_num, line);
                first_found = 1;
                break;
            } else if (mode == 'a') {
                printf("Line %d: %s", line_num, line);
            }
        }
        line_num++;
    }

    if (mode == 'c') {
        printf("Total occurrences of '%s' in '%s': %d\n", pattern, filename, occurrence_count);
    } else if (mode == 'f' && !first_found) {
        printf("Pattern '%s' not found in file '%s'.\n", pattern, filename);
    }
    fclose(fp);
}

int main() {
    char input[256];
    char *args[20];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = 0;

        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (argc == 0) continue;

        if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
            printf("Exiting shell.\n");
            break;
        }

        // Handle custom command: search <f|c|a> <pattern> <filename>
        if (strcmp(args[0], "search") == 0) {
            if (argc < 4) {
                printf("Usage: search <f|c|a> <pattern> <filename>\n");
            } else {
                search_file(args[1][0], args[2], args[3]);
            }
            continue;
        }

        // External system commands
        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                perror("Command execution failed");
                exit(1);
            }
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            perror("fork failed");
        }
    }
    return 0;
}
