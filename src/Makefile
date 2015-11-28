CFLAGS = -Werror -pedantic-errors

lpl: liblpl 
	$(CC) $(CFLAGS) lpl.c -I./parser -I./parser/nodes -L./parser -llpl -o lpl

liblpl:
	$(MAKE) -C parser liblpl 

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C tip  clean
	rm lpl.o lpl 
