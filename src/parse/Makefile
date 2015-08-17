parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	mv lpl_parser.c lpl_parser.cpp
	g++ -I ../node -Werror  -pedantic-errors -g -c -o lpl_parser.o lpl_parser.cpp


scanner.o: lpl_scanner.l
	flex --outfile=lpl_scanner.cpp --header-file=lpl_scanner.h lpl_scanner.l
	gcc -I ../node -Werror  -pedantic-errors -g -c -o lpl_scanner.o lpl_scanner.cpp

all: parser.o scanner.o

clean: 
	rm -rf lpl_scanner.cpp lpl_scanner.h 
	rm -rf lpl_parser.cpp lpl_parser.h lpl_parser.out lpl_parser.o lpl_scanner.o
