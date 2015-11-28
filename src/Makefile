lpl: liblpl 
	gcc -static lpl.c -I./parser -I./parser/nodes -Werror  -pedantic-errors -L./parser -llpl -o lpl

liblpl:
	$(MAKE) -C parser liblpl 

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C tip  clean
	rm lpl.o lpl 
