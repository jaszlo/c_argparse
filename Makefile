# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -g

# Directories
SRC_DIR := src
BUILD_DIR := build

### Test-Cases
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')# Find all source files recursively in src directory
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))# Create a list of object files based on source file locations
TEST_SRC := src/test.c# Test source file
TARGET := test# Target executable for Test-Cases

# Library
LIB_SRCS := $(SRC_DIR)/argparse.c $(SRC_DIR)/helpers.c# Library source files
LIB_NAME := argparse.so# Library name

### Test-Cases
all: clean $(BUILD_DIR) $(TARGET)

set_prod:
	$(eval OPTIMIZATION_FLAGS := -O3)

set_gdb:
	$(eval DEBUG_FLAGS := -D GDB)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OPTIMIZATION_FLAGS) -c $< -o $@


# Link all object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile the library
# fPIC: Position Independent Code
# shared: Create a shared library
lib: clean
	@echo "Compiling library..."
	@$(CC) $(CFLAGS) -O3 -shared -fPIC $(LIB_SRCS) -o $(LIB_NAME)

test_so: lib
	@echo "Running dynamic library test..."
	@$(CC) $(CFLAGS) -L. -o test_so test_so.c -l:argparse.so
	@export LD_LIBRARY_PATH=.$$LD_LIBRARY_PATH

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(LIB_NAME) ./test_so

run:
	./$(TARGET)

gdb: clean set_gdb all
	gdb ./$(TARGET) --command=.gdb_init

valgrind: clean set_gdb all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

.PHONY: all clean run gdb valgrind set_gdb set_prod debug
