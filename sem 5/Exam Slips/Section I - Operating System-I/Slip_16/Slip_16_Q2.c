/*
 * Lab Course: CS-305-MJ-P (Operating System-I)
 * Slip No: 01 - Question 2
 * 
 * Q.2) Write a C program that behaves like a shell which displays the command
 *      prompt '$'. It accepts the command, tokenize the command line and
 *      execute it by creating the child process. Also implement the additional
 *      command 'count' as:
 *      a. $ count c filename: It will display the number of characters in given file
 *      b. $ count w filename: It will display the number of words in given file
 *      c. $ count l filename: It will display the number of lines in given file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

// Function to implement the custom 'count' command
void execute_count(char *mode, char *filename) {
    if (mode == NULL || filename == NULL) {
        printf("Usage: count <c|w|l> <filename>\n");
        printf("  c : count characters\n");
        printf("  w : count words\n");
        printf("  l : count lines\n");
        return;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    long char_count = 0;
    long word_count = 0;
    long line_count = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        char_count++;

        if (ch == '\n') {
            line_count++;
        }

        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            word_count++;
        }
    }
    fclose(fp);

    if (strcmp(mode, "c") == 0) {
        printf("Total characters in '%s': %ld\n", filename, char_count);
    } else if (strcmp(mode, "w") == 0) {
        printf("Total words in '%s': %ld\n", filename, word_count);
    } else if (strcmp(mode, "l") == 0) {
        printf("Total lines in '%s': %ld\n", filename, line_count);
    } else {
        printf("Invalid count mode '%s'. Use 'c', 'w', or 'l'.\n", mode);
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        // Display command prompt
        printf("$ ");
        fflush(stdout);

        // Read command line
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        // Remove trailing newline
        line[strcspn(line, "\r\n")] = '\0';

        // Ignore empty input
        if (strlen(line) == 0) {
            continue;
        }

        // Tokenize command line
        int argc = 0;
        char *token = strtok(line, " \t");
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " \t");
        }
        args[argc] = NULL;

        if (argc == 0) {
            continue;
        }

        // Check for exit / quit
        if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0) {
            printf("Exiting shell.\n");
            break;
        }

        // Check for custom command 'count'
        if (strcmp(args[0], "count") == 0) {
            if (argc < 3) {
                printf("Usage: count <c|w|l> <filename>\n");
            } else {
                execute_count(args[1], args[2]);
            }
            continue;
        }

        // Execute external system command via fork & execvp
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
        } else if (pid == 0) {
            // Child process executes command
            if (execvp(args[0], args) == -1) {
                printf("%s: command not found\n", args[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process waits for child to complete
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
