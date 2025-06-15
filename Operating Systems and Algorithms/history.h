#ifndef __HISTORY_H
#define __HISTORY_H

// typedef struct CommandHistory{
//     char *commands[MAX_HISTORY_SIZE];
//     int size;
// } CommandHistory;

// Function declarations (forward declarations)
// void add_command(CommandHistory *history, char *command);
// Function to create command history
CommandHistory *create_history();
// Function to load history from a file
void load_history(CommandHistory *history);
// Function to save history to a file
void save_history(CommandHistory *history);

// Function to add a command to the history
void add_command(CommandHistory *history, char *command);
// Function to display command history
void show_history(CommandHistory *history, int num_entries);

// Function to free the memory used for command history
void free_history(CommandHistory *history);

#endif