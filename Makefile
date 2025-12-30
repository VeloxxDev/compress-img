CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -Iinclude

BIN_DIR = bin

SRC = src/histo.c src/image.c src/ppmhist.c
OBJ = $(BIN_DIR)/histo.o $(BIN_DIR)/image.o $(BIN_DIR)/ppmhist.o

TEST_SRC = tests/test_histo.c
TEST_OBJ = $(BIN_DIR)/test_histo.o

ppmhist: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ppmhist

# --- Compilation des .o dans bin/ ---
$(BIN_DIR)/%.o: src/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: tests/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Tests ---
tests: $(TEST_OBJ) $(BIN_DIR)/histo.o $(BIN_DIR)/image.o
	$(CC) $(CFLAGS) $(TEST_OBJ) $(BIN_DIR)/histo.o $(BIN_DIR)/image.o -o test_histo
	./test_histo

clean:
	rm -f $(BIN_DIR)/*.o ppmhist test_histo
