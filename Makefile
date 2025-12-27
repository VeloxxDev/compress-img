# ============================
#        VARIABLES
# ============================

CC      := gcc
CFLAGS  := -pedantic -Wall -Wextra -Werror -Iinclude 
LDFLAGS := 

SRC     := main.c histo.c mapping.c quantification.c ppmhist.c
OBJ     := $(SRC:.c=.o)

TEST_SRC := tests/tests.c histo.c mapping.c quantification.c ppmhist.c
TEST_OBJ := $(TEST_SRC:.c=.o)

NAME    := ppmhist
TEST_BIN := tests_bin

# ============================
#        RULES
# ============================

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compilation générique
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ============================
#        TESTS
# ============================

tests: $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $(TEST_BIN)

run_tests: tests
	./$(TEST_BIN)

# ============================
#        CLEANING
# ============================

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_BIN)

re: fclean all

# ============================
#        PHONY
# ============================

.PHONY: all clean fclean re tests run_tests
