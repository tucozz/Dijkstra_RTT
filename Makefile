# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./headers

# Directories
SRC_DIR = src
ALGORITHMS_DIR = $(SRC_DIR)/algorithms
DATA_STRUCTURES_DIR = $(SRC_DIR)/data_structures
IO_DIR = $(SRC_DIR)/Input_Output
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(ALGORITHMS_DIR)/*.c) $(wildcard $(DATA_STRUCTURES_DIR)/*.c) $(wildcard $(IO_DIR)/*.c) main.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Executable name
EXECUTABLE = my_program

# Main target
all: $(BIN_DIR)/$(EXECUTABLE)

# Linking rule
$(BIN_DIR)/$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR) $(OBJ_DIR)/algorithms $(OBJ_DIR)/data_structures $(OBJ_DIR)/Input_Output $(BIN_DIR):
	mkdir -p $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
