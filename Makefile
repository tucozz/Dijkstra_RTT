# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./headers

# Directories
SRC_DIR = src
ALGORITHMS_DIR = $(SRC_DIR)/algorithms
DATA_STRUCTURES_DIR = $(SRC_DIR)/data_structures
IO_DIR = $(SRC_DIR)/Input_Output
OBJ_DIR = obj
OBJ_ALGORITHMS_DIR = $(OBJ_DIR)/algorithms
OBJ_DATA_STRUCTURES_DIR = $(OBJ_DIR)/data_structures
OBJ_IO_DIR = $(OBJ_DIR)/Input_Output

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(ALGORITHMS_DIR)/*.c) $(wildcard $(DATA_STRUCTURES_DIR)/*.c) $(wildcard $(IO_DIR)/*.c) main.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Executable name
EXECUTABLE = trab2

# Main target
all: $(EXECUTABLE)

# Linking rule
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_ALGORITHMS_DIR)/%.o: $(ALGORITHMS_DIR)/%.c | $(OBJ_ALGORITHMS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DATA_STRUCTURES_DIR)/%.o: $(DATA_STRUCTURES_DIR)/%.c | $(OBJ_DATA_STRUCTURES_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_IO_DIR)/%.o: $(IO_DIR)/%.c | $(OBJ_IO_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR) $(OBJ_ALGORITHMS_DIR) $(OBJ_DATA_STRUCTURES_DIR) $(OBJ_IO_DIR):
	mkdir -p $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean

