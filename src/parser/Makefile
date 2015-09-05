libparser: lpl_scanner.o lpl_parser.o nodes
	g++ -I ./node -Werror -pedantic-errors -g -c parser.cpp -o parser.o
	ar rcs libparser.a parser.o lpl_parser.o lpl_scanner.o ./node/*.o

lpl_parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	mv lpl_parser.c lpl_parser.cpp
	g++ -I ./node -Werror  -pedantic-errors -g -c -o lpl_parser.o lpl_parser.cpp


lpl_scanner.o: lpl_parser.o lpl_scanner.l
	flex --outfile=lpl_scanner.cpp --header-file=lpl_scanner.h lpl_scanner.l
	gcc -I ./node -Werror  -pedantic-errors -g -c -o lpl_scanner.o lpl_scanner.cpp

nodes:
	$(MAKE) -C node all 

all: lpl_parser.o lpl_scanner.o

clean: 
	rm -rf lpl_scanner.cpp lpl_scanner.h 
	rm -rf lpl_parser.cpp lpl_parser.h lpl_parser.out lpl_parser.o lpl_scanner.o
	rm -rf parser.o libparser.a
