CC=gcc
CFLAGS1=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
CFLAGS2=-Wall -Werror -std=gnu99 -pedantic -O3 $(OTHERFLAGS)

poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
	gcc -o $@ $(CFLAGS1) $^
poker_fast: cards.o  deck.o  eval.o  future.o  input.o  main.o
	gcc -o $@ $(CFLAGS2) $^
clean:
	rm -rf *.o poker *~
