main: main.o parser.o scanner.o node.o
	g++ lpl_parser.o lpl_scanner.o node.o main.o -o main

main.o: main.c parser.o scanner.o 
	gcc -c main.c -o main.o 

parser.o: lpl_parser.y 
	lemon lpl_parser.y -s
	gcc -c -o lpl_parser.o lpl_parser.c

node.o: node.h node.c
	gcc -c -o node.o node.c

scanner.o: lpl_scanner.l
	flex --outfile=lpl_scanner.c --header-file=lpl_scanner.h lpl_scanner.l
	gcc -c -o lpl_scanner.o lpl_scanner.c

clean:
	rm -rf lpl_parser.c* lpl_parser.h* lpl_parser.out lpl_parser.o
	rm -rf lpl_scanner.c lpl_scanner.h lpl_scanner.o
	rm -rf node.o
	rm -rf main main.o
