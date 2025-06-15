#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <ctype.h>

#define MAX_HISTORY_SIZE 20
#define COMMAND_LENGTH 1024
#define DEFAULT_OUTPUT_SIZE 10
#define HISTORY_FILE ".shell_history"

// CommandHistory structure to store past commands
typedef struct CommandHistory{
    char *commands[MAX_HISTORY_SIZE];
    int size;
} CommandHistory;

char previous_directory[PATH_MAX];

// Function declarations (forward declarations)
void add_command(CommandHistory *history, char *command);

// Function to display the custom shell prompt
void display_prompt() {
    char hostname[HOST_NAME_MAX];
    char cwd[PATH_MAX];
    struct passwd *pw = getpwuid(getuid());
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));

    const char *home = pw->pw_dir;
    if (strncmp(cwd, home, strlen(home)) == 0) {
        printf("<%s@%s:~%s> ", pw->pw_name, hostname, cwd + strlen(home));
    } else {
        printf("<%s@%s:%s> ", pw->pw_name, hostname, cwd);
    }
}

// Function to run the 'pwd' command
void run_pwd() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

// Function to run the 'echo' command
void run_echo(char *args) {
    size_t length = strlen(args);
    if ((args[0] == '"' && args[length - 1] == '"') || (args[0] == '\'' && args[length - 1] == '\'')) {
        args[length - 1] = '\0';
        printf("%s\n", args + 1);
    } else {
        char *token = strtok(args, " \t");
        int first = 1;

        while (token != NULL) {
            if (!first) {
                printf(" ");
            }
            printf("%s", token);
            token = strtok(NULL, " \t");
            first = 0;
        }
        printf("\n");
    }
}

// Function to run the 'cd' command
void run_cd(char *path) {
    char current_directory[PATH_MAX];
    getcwd(current_directory, sizeof(current_directory));

    if (path != NULL && strtok(NULL, " \t") != NULL) {
        printf("cd: too many arguments\n");
        return;
    }

    if (path == NULL || strcmp(path, "~") == 0) {
        path = getenv("HOME");
    } else if (strcmp(path, "-") == 0) {
        if (previous_directory[0] != '\0') {
            printf("%s\n", previous_directory);
            path = previous_directory;
        } else {
            printf("cd: OLDPWD not set\n");
            return;
        }
    }

    if (chdir(path) == 0) {
        strcpy(previous_directory, current_directory);
    } else {
        perror("cd");
    }
}

// Function to create command history
CommandHistory *create_history() {
    CommandHistory *history = (CommandHistory *)malloc(sizeof(CommandHistory));
    history->size = 0;
    for (int i = 0; i < MAX_HISTORY_SIZE; i++) {
        history->commands[i] = NULL;
    }
    return history;
}

// Function to load history from a file
void load_history(CommandHistory *history) {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) return;

    char line[COMMAND_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        add_command(history, line);
    }
    fclose(file);
}

// Function to save history to a file
void save_history(CommandHistory *history) {
    FILE *file = fopen(HISTORY_FILE, "w");
    if (file == NULL) return;

    for (int i = 0; i < history->size; i++) {
        fprintf(file, "%s\n", history->commands[i]);
    }
    fclose(file);
}

// Function to add a command to the history
void add_command(CommandHistory *history, char *command) {
    // Don't add the command if it's a duplicate of the last one
    if (history->size > 0 && strcmp(history->commands[history->size - 1], command) == 0) {
        return;
    }

    if (history->size < MAX_HISTORY_SIZE) {
        history->commands[history->size] = strdup(command);
        history->size++;
    } else {
        free(history->commands[0]);
        for (int i = 1; i < MAX_HISTORY_SIZE; i++) {
            history->commands[i - 1] = history->commands[i];
        }
        history->commands[MAX_HISTORY_SIZE - 1] = strdup(command);
    }
}

// Function to display command history
void show_history(CommandHistory *history, int num_entries) {
    if (num_entries > history->size) {
        num_entries = history->size;
    }
    for (int i = history->size - num_entries; i < history->size; i++) {
        printf("%d %s\n", i + 1, history->commands[i]);
    }
}

// Function to handle user commands
void handle_command(char *command, CommandHistory *history) {
    add_command(history, command);

    char *cmd = strtok(command, " \t");
    if (cmd == NULL) return;

    if (strcmp(cmd, "pwd") == 0) {
        run_pwd();
    } else if (strcmp(cmd, "echo") == 0) {
        run_echo(strtok(NULL, ""));
    } else if (strcmp(cmd, "cd") == 0) {
        run_cd(strtok(NULL, " \t"));
    } else if (strcmp(cmd, "history") == 0) {
        char *num_arg = strtok(NULL, " \t");
        int num_entries = DEFAULT_OUTPUT_SIZE;

        if (num_arg != NULL) {
            num_entries = atoi(num_arg);
        }
        show_history(history, num_entries);
    } else {
        system(command);
    }
}

// Function to free the memory used for command history
void free_history(CommandHistory *history) {
    for (int i = 0; i < history->size; i++) {
        free(history->commands[i]);
    }
    free(history);
}

// Main function to run the shell
int main() {
    char command[COMMAND_LENGTH];
    CommandHistory *history = create_history();
    load_history(history);

    while (1) {
        display_prompt();
        if (fgets(command, sizeof(command), stdin) == NULL) break;

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            save_history(history);
            break;
        }

        handle_command(command, history);
    }

    free_history(history);
    return 0;
}
