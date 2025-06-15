#ifndef HEADERS_H_
#define HEADERS_H_

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
typedef struct CommandHistory {
    char *commands[MAX_HISTORY_SIZE];
    int size;
} CommandHistory;

extern char previous_directory[PATH_MAX];

#include "display_prompt.h"
#include "echo.h"
#include "history.h"
#include "pwd.h"
#include "cd.h"

#endif