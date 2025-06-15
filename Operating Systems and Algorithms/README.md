Overview :

This project implements a custom shell in C that provides basic functionalities similar to a Unix shell. It includes built-in commands such as pwd, echo, cd, and a command history feature.

Features :

    Custom Shell Prompt: Displays in the format <username@system_name:current_dir>.
    Built-in Commands:
        pwd: Prints the current working directory.
        echo: Displays text while handling multiple spaces and tabs.
        cd: Changes the current working directory with support for various options (~, .., -, and ., along with error handling).
    Command History: Stores the last 20 unique commands across sessions.

Using the Shell

Once the shell is running, you will see a prompt in the format <username@system_name:current_dir>.
Commands

    1.pwd: Displays the current working directory.
    2.echo <string>: Displays the input string, normalizing multiple spaces or tabs.
    3.cd <directory>: Changes the current directory.

    * Without arguments: Changes to the home directory.
    * With ..: Moves one level up.
    * With -: Changes to the previous directory and displays it.
    * With ~: Changes to the home directory.
    * Error handling for invalid inputs (e.g., too     many arguments).
    4.Command History: Automatically saves the last 20 commands and gives the last 10 commands as default output. You can access the history using the history command.

    The history persists across sessions.

Code Structure

The code is modular and includes the following functions:

    display_prompt(): Displays the shell prompt.
    run_pwd(): Executes the pwd command.
    run_echo(char *args): Executes the echo command.
    run_cd(char *path): Executes the cd command.
    create_history(): Initializes the command history.
    load_history(CommandHistory *history): Loads command history from a file.
    save_history(CommandHistory *history): Saves command history to a file.

Make file :
Created .h and .c files for the functions cd,pwd,echo,history,display_prompt

created a file code.c which has the whole code .

