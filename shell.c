#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

// Function to execute a command
void execute_command(char *input) {
    char *args[MAX_ARGS];
    char *input_file = NULL, *output_file = NULL;
    int in_fd, out_fd;
    int is_background = 0;

    // Check for background execution
    if (input[strlen(input) - 1] == '&') {
        is_background = 1;
        input[strlen(input) - 1] = '\0';  // Remove '&' from input
    }

    // Check for input (`<`) and output (`>`) redirection
    char *input_redirect = strchr(input, '<');
    char *output_redirect = strchr(input, '>');

    if (input_redirect) {
        *input_redirect = '\0';
        input_file = strtok(input_redirect + 1, " ");
    }
    if (output_redirect) {
        *output_redirect = '\0';
        output_file = strtok(output_redirect + 1, " ");
    }

    // Tokenize command
    char *token = strtok(input, " ");
    int arg_count = 0;
    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    if (arg_count == 0) return;

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {  // Child process
        if (input_file) {
            in_fd = open(input_file, O_RDONLY);
            if (in_fd < 0) {
                perror("Error opening input file");
                exit(1);
            }
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        if (output_file) {
            out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out_fd < 0) {
                perror("Error opening output file");
                exit(1);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        execvp(args[0], args);
        perror("Command execution failed");
        exit(1);
    } else {  // Parent process
        if (!is_background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("Process running in background (PID: %d)\n", pid);
        }
    }
}

// Function to execute multiple piped commands
void execute_piped_commands(char *input) {
    char *commands[MAX_ARGS];
    int cmd_count = 0;
    char *token = strtok(input, "|");

    while (token != NULL) {
        commands[cmd_count++] = token;
        token = strtok(NULL, "|");
    }

    if (cmd_count < 2) {
        execute_command(input);
        return;
    }

    int pipe_fds[cmd_count - 1][2];
    pid_t pids[cmd_count];

    for (int i = 0; i < cmd_count; i++) {
        if (i < cmd_count - 1 && pipe(pipe_fds[i]) == -1) {
            perror("Pipe failed");
            return;
        }

        pids[i] = fork();
        if (pids[i] == -1) {
            perror("Fork failed");
            return;
        }

        if (pids[i] == 0) {  // Child process
            if (i > 0) {  // Redirect stdin if not first command
                dup2(pipe_fds[i - 1][0], STDIN_FILENO);
                close(pipe_fds[i - 1][0]);
            }

            if (i < cmd_count - 1) {  // Redirect stdout if not last command
                dup2(pipe_fds[i][1], STDOUT_FILENO);
                close(pipe_fds[i][1]);
            }

            for (int j = 0; j < cmd_count - 1; j++) {
                close(pipe_fds[j][0]);
                close(pipe_fds[j][1]);
            }

            execute_command(commands[i]);
            exit(0);
        }
    }

    // Close all pipes in the parent
    for (int i = 0; i < cmd_count - 1; i++) {
        close(pipe_fds[i][0]);
        close(pipe_fds[i][1]);
    }

    // Wait for all processes
    for (int i = 0; i < cmd_count; i++) {
        waitpid(pids[i], NULL, 0);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("WHATTHESHELL> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) continue;

        if (strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        if (strchr(input, '|')) {
            execute_piped_commands(input);
        } else {
            execute_command(input);
        }
    }

    return 0;
}

