main: main.o parser.o scanner.o node.o
	gcc -Werror  -pedantic-errors -g parse/lpl_parser.o parse/lpl_scanner.o node/node.o main.o -o main

main.o: main.c parser.o scanner.o 
	gcc -Werror  -pedantic-errors -g -c main.c -o main.o

parser.o:
	$(MAKE) -C parse

node.o:
	$(MAKE) -C node 

clean:
	rm -rf lpl_parser.c* lpl_parser.h* lpl_parser.out lpl_parser.o
	rm -rf lpl_scanner.c lpl_scanner.h lpl_scanner.o
	rm -rf node.o
	rm -rf main main.o
