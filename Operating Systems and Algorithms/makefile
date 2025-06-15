# Variables
CC = gcc
CFLAGS = -g -Wall
TARGET = output
SRC = main.c cd.c pwd.c echo.c history.c display_prompt.c
OBJ = $(SRC:.c=.o)

# Default target to build the program
all: $(TARGET)

# Rule to link object files and create the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files into object files.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
build: $(TARGET)# echo "Build complete: $(TARGET)"
