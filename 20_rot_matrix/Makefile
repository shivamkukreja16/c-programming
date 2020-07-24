CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99 -Wsign-compare -Wwrite-strings -Wtype-limits -fsanitize=address

all: read-matrix.o rotate.o
	$(CC) $(CFLAGS) -o rotate-matrix read-matrix.o rotate.o

rotate.o: rotate.c
	$(CC) $(CFLAGS) -c rotate.c

.PHONY: clean
clean:
	rm -f rotate-matrix *.c~ Makefile~ rotate.o
