main: main.o parser.o scanner.o node.o
	g++ main.o lpl_parser.o lpl_scanner.o node.o -o main

main.o: main.cpp parser.o scanner.o
	g++ -c main.cpp -o main.o

parser.o: lpl_parser.y 
	lemon lpl_parser.y -s
	mv lpl_parser.c lpl_parser.cpp
	gcc -c -o lpl_parser.o lpl_parser.cpp

node.o: node.h node.cpp
	gcc -c -o node.o node.cpp

scanner.o: lpl_scanner.l
	flex --outfile=lpl_scanner.cpp --header-file=lpl_scanner.h lpl_scanner.l
	g++ -c -o lpl_scanner.o lpl_scanner.cpp

clean:
	rm -rf lpl_parser.c* lpl_parser.h* lpl_parser.out lpl_parser.o
	rm -rf lpl_scanner.cpp lpl_scanner.h lpl_scanner.o
	rm -rf main main.o
