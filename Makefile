CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -Iinclude

BIN_DIR = bin

SRC = src/histo.c src/image.c src/ppmhist.c src/quantification.c
OBJ = $(BIN_DIR)/histo.o $(BIN_DIR)/image.o $(BIN_DIR)/ppmhist.o $(BIN_DIR)/quantification.o

TEST_HISTO_SRC = tests/test_histo.c
TEST_HISTO_OBJ = $(BIN_DIR)/test_histo.o


ppmhist: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ppmhist

$(BIN_DIR)/%.o: src/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: tests/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


tests: $(TEST_HISTO_OBJ) $(TEST_PPMHIST_OBJ) $(BIN_DIR)/histo.o $(BIN_DIR)/image.o
	$(CC) $(CFLAGS) $(TEST_HISTO_OBJ) $(BIN_DIR)/histo.o $(BIN_DIR)/image.o -o test_histo
	./test_histo

clean:
	rm -f $(BIN_DIR)/*.o ppmhist test_histo
