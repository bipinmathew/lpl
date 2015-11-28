main: main.o parser.o scanner.o node.o
	gcc -I./node -Werror  -pedantic-errors parser/lpl_parser.o parser/lpl_scanner.o parser/nodes/node.o main.o -o main

main.o: main.c parser.o scanner.o 
	gcc -I./parser/nodes -I./parser -Werror  -pedantic-errors -c main.c -o main.o

parser.o:
	$(MAKE) -C parser parser.o

scanner.o:
	$(MAKE) -C parser scanner.o

node.o:
	$(MAKE) -C parser/nodes 

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C parser/nodes clean
	$(MAKE) -C tip  clean
	rm main.o main
