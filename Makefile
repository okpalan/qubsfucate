# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -Isrc -Isrc/quparse  # Ensure correct include paths

# Directories
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build/obj
BIN_DIR = build/bin

# Source files and objects
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Test files
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output binary
TEST_BIN = $(BIN_DIR)/test_runner

# Targets
all: $(TEST_BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(OBJ_FILES) $(TEST_OBJ_FILES) -o $(TEST_BIN)

# Run tests
test: $(TEST_BIN)
	$(TEST_BIN)

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(TEST_BIN)

# Create necessary directories
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@
