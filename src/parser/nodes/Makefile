CFLAGS = -Werror -pedantic-errors

node.o: node.h node.c
	$(CC) $(CFLAGS) -c -o node.o node.c

all: node.o

clean:
	rm -rf node.o
