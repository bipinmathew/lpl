lpl: lpl.o parser.o scanner.o nodes
	g++ -Werror  -pedantic-errors -g parse/lpl_parser.o parse/lpl_scanner.o node/*.o lpl.o -o lpl

lpl.o: lpl.cpp parser.o scanner.o 
	g++ -I./node -I./parse -Werror  -pedantic-errors -g -c lpl.cpp -o lpl.o

parser.o:
	$(MAKE) -C parse parser.o

scanner.o:
	$(MAKE) -C parse scanner.o

nodes:
	$(MAKE) -C node all

clean:
	$(MAKE) -C parse clean
	$(MAKE) -C node clean
	$(MAKE) -C tip  clean
	rm lpl.o lpl
