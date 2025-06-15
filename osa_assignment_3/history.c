#include "headers.h"
#include "history.h"

// Function declarations (forward declarations)
// void add_command(CommandHistory *history, char *command);
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

// Function to free the memory used for command history
void free_history(CommandHistory *history) {
    for (int i = 0; i < history->size; i++) {
        free(history->commands[i]);
    }
    free(history);
}
