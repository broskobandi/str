# Project
PROJECT := str
FIND_CC := $(shell command -v clang || command -v gcc)
CC := $(FIND_CC)
CFLAGS := -Wall -Wextra -Werror -Wconversion -Wunused-result
CPPFLAGS := -Iinclude -Isrc
LDFLAGS := -L/usr/local/lib -lvec

# Dirs
BUILD_DIR := build
SRC_DIR := src
INC_DIR := include
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include
OBJ_DIR := $(BUILD_DIR)/obj
TEST_DIR := test
DOC_DIR := doc
EXAMPLE_DIR := example

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(INC_DIR)/$(PROJECT).h
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so
TEST_MAIN := $(TEST_DIR)/test.c
TEST_EXE := $(BUILD_DIR)/test
EXAMPLE_EXE := $(BUILD_DIR)/example
EXAMPLE_MAIN := $(EXAMPLE_DIR)/example.c

# Rules
.PHONY: all test clean install uninstall example doc

all: $(LIB_A) $(LIB_SO)

test: CC := bear -- $(FIND_CC)
test: $(TEST_EXE)
	./$<

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR) compile_commands.json

install:
	cp $(LIB_A) $(LIB_INSTALL_DIR)
	cp $(LIB_SO) $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

uninstall:
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_A)))
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_SO)))
	rm $(addprefix $(INC_INSTALL_DIR)/, $(notdir $(INC)))

example: LDFLAGS := -L/usr/local/lib -lstr
example: $(EXAMPLE_EXE)
	./$<

doc:
	doxygen

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXE): $(TEST_MAIN) $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(EXAMPLE_EXE): $(EXAMPLE_MAIN) | $(BUILD_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
