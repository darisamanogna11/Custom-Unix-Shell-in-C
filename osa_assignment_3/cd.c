#include "headers.h"
#include "cd.h"

// Function declarations (forward declarations)
// void add_command(CommandHistory *history, char *command);


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
