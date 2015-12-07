CFLAGS = -std=c99 -Werror -pedantic-errors
debug: CFLAGS += -DDEBUG -g
debug: lpl

production: CFLAGS += -O3
production: lpl
production:
	strip lpl


export CFLAGS


lpl: liblpl
	$(CC) $(CFLAGS) lpl.c -I./parser -I./parser/nodes -L./parser -llpl -o lpl

tests: liblpl
	$(MAKE) -C test all

liblpl:
	$(MAKE) -C parser liblpl

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C tip  clean
	rm lpl.o lpl
