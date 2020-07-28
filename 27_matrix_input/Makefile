CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99 -Wsign-compare -Wwrite-strings -Wtype-limits -fsanitize=address

rotateMatrix: rotateMatrix.c
	$(CC) -o rotateMatrix $(CFLAGS) rotateMatrix.c

.PHONY: clean
clean:
	rm -f *.c~ Makefile~
