#include "headers.h"
#include "display_prompt.h"

// Function declarations (forward declarations)
// void add_command(CommandHistory *history, char *command);


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