CC = gcc
CFLAGS = -Wall -g
SRC_DIR = ../src
OBJ_DIR = ./obj
BIN_DIR = ../bin
INCLUDE_DIR = ../include

# Files to be compiled
SRCS = $(SRC_DIR)/quparse/quparse.c
OBJS = $(OBJ_DIR)/quparse.o
EXEC = $(BIN_DIR)/quparse.exe

# Default target
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/quparse/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

# Phony targets
.PHONY: all clean
