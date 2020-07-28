CFLAGS = -g -Wall -Werror -pedantic -std=gnu99
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

test-c4deck: $(OBJS)
    gcc $(CFLAGS) -o $@ $(OBJS)
%.o: %.c
    gcc $(CFLAGS) -c $<
deck.o: deck.h
cards.o: cards.h
eval.o: eval.h

.PHONY: clean
clean:
    rm -f test-c4deck *.o *.c~ *.h~
