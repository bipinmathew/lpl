CFLAGS = -std=c99 -Werror -pedantic-errors
debug: CFLAGS += -DDEBUG -g
debug: lpl

production: CFLAGS += -O3
production: lpl
production:
	strip lpl


export CFLAGS


lpl: liblpl
	$(CC) $(CFLAGS) src/lpl.c -I./libparser -I./libparser/nodes -L./libparser -llpl -o lpl

tests: liblpl
	$(MAKE) -C test all

liblpl:
	$(MAKE) -C libparser liblpl

clean:
	$(MAKE) -C libparser clean
	$(MAKE) -C tip  clean
	rm lpl.o lpl
