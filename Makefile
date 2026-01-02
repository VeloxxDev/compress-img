CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -Iinclude

BIN_DIR = bin

SRC = src/histo.c src/image.c src/main.c src/quantification.c
OBJ = $(BIN_DIR)/histo.o $(BIN_DIR)/image.o $(BIN_DIR)/main.o $(BIN_DIR)/quantification.o

TEST_HISTO_SRC = tests/test_histo.c
TEST_HISTO_OBJ = $(BIN_DIR)/test_histo.o


# --- Programme principal ---
main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main


# --- Compilation des .o venant de src/ ---
$(BIN_DIR)/%.o: src/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# --- Compilation des .o venant de tests/ ---
$(BIN_DIR)/%.o: tests/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# --- Tests unitaires ---
tests: $(TEST_HISTO_OBJ) $(BIN_DIR)/histo.o $(BIN_DIR)/image.o
	$(CC) $(CFLAGS) $(TEST_HISTO_OBJ) $(BIN_DIR)/histo.o $(BIN_DIR)/image.o -o test_histo
	./test_histo


# --- Compilation de ppmhist.c ---
ppmhist: $(BIN_DIR)/histo.o $(BIN_DIR)/image.o $(BIN_DIR)/quantification.o $(BIN_DIR)/mapping.o $(BIN_DIR)/ppmhist.o
	$(CC) $(CFLAGS) $^ -o ppmhist


# --- Compilation de ppmhist.c ---
$(BIN_DIR)/ppmhist.o: src/ppmhist.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# --- Nettoyage ---
clean:
	rm -f $(BIN_DIR)/*.o main ppmhist test_histo *.ppm
	
