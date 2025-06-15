#include "headers.h"
#include "display_prompt.h"
#include "echo.h"
#include "history.h"
#include "pwd.h"
#include "cd.h"
#define MAX_HISTORY_SIZE 20
#define COMMAND_LENGTH 1024
#define DEFAULT_OUTPUT_SIZE 10
#define HISTORY_FILE ".shell_history"

// CommandHistory structure to store past commands
// typedef struct CommandHistory{
//     char *commands[MAX_HISTORY_SIZE];
//     int size;
// } CommandHistory;

char previous_directory[PATH_MAX];

// Function declarations (forward declarations)
void add_command(CommandHistory *history, char *command);


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
