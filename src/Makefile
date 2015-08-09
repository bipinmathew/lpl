main: main.o parser.o scanner.o node.o
	gcc -I./node -Werror  -pedantic-errors -g parse/lpl_parser.o parse/lpl_scanner.o node/node.o main.o -o main

main.o: main.c parser.o scanner.o 
	gcc -I./node -I./parse -Werror  -pedantic-errors -g -c main.c -o main.o

parser.o:
	$(MAKE) -C parse parser.o

scanner.o:
	$(MAKE) -C parse scanner.o

node.o:
	$(MAKE) -C node 

clean:
	$(MAKE) -C parse clean
	$(MAKE) -C node clean
	$(MAKE) -C tip  clean
	rm main.o main
