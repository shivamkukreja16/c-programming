CC=gcc
CFLAGS=-std=gnu99 -Wall -Wsign-compare -Wwrite-strings -Wtype-limits -Werror -pedantic -fsanitize=address

test: test.c
	$(CC) $(CFLAGS) -o test test.c

.PHONY: clean
clean:
	rm -f test *.c~ Makefile~ *.o
