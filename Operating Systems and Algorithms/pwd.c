#include "headers.h"
#include "pwd.h"


// Function to run the 'pwd' command
void run_pwd() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}
