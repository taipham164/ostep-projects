CC=gcc
CFLAGS=-Wall -Werror -std=c99

reverse: reverse.c
	$(CC) $(CFLAGS) -o reverse reverse.c

clean:
	rm -f reverse

test: reverse
	./test-reverse.sh

.PHONY: clean test
