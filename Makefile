
CC=gcc
CFLAGS=-Wall -ansi -pedantic
LDFLAGS=
EXEC=typo
BIN=typo.o main.o
SRC=typo.c main.c
HEAD=typo.h

all: $(EXEC)

typo: $(BIN)
	$(CC) -o typo $(BIN) $(LDFLAGS)

%.o: %.c $(HEAD)
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o *~ 2> /dev/null

clear: clean
	rm -f $(EXEC) $(USER)_typo.tgz 2> /dev/null

zip: clear
	mkdir -p $(USER)_typo
	cp Makefile *.c *.h *.sok $(USER)_typo
	tar czf $(USER)_typo.tgz $(USER)_typo
	rm -rf $(USER)_typo
