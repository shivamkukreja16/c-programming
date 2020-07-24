CFLAGS=-std=gnu99 -Wall -Wsign-compare -Wwrite-strings -Wtype-limits -Werror -pedantic

test : test.c
	gcc $(CFLAGS) -o test test.c

.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~
  
