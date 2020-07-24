CC=gcc
CFLAGS=-std=gnu99 -Wall -Wsign-compare -Wwrite-strings -Wtype-limits -Werror -pedantic -fsanitize=address

subseq: maxSeq.o test-subseq.o
	$(CC) $(CFLAGS) -o subseq maxSeq.o test-subseq.o

maxSeq.o: maxSeq.c
	$(CC) $(CFLAGS) -c maxSeq.c

test-subseq.o : test-subseq.c
	$(CC) -Wall -std=gnu99 -c test-subseq.c


.PHONY: clean
clean:
	rm -f subseq *.c~ Makefile~ *.o
  
