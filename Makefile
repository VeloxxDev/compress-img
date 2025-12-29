CFLAGS = -Wall -Wextra -std=c99 -Iinclude

SRC = src/histo.c src/image.c src/ppmhist.c
OBJ = $(SRC:.c=.o)

ppmhist: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o ppmhist

clean:
	rm -f $(OBJ) ppmhist
