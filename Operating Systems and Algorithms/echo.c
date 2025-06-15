#include "headers.h"
#include "echo.h"

// Function declarations (forward declarations)
// void add_command(CommandHistory *history, char *command);


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
