all: libparser 

libparser: lpl_scanner.o lpl_parser.o
	$(MAKE) -C nodes all 
	g++ -std=c++11 -I ./nodes -Werror -pedantic-errors -g  -c parser.cpp -o parser.o
	ar rcs libparser.a parser.o lpl_parser.o lpl_scanner.o ./nodes/*.o

lpl_parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	mv lpl_parser.c lpl_parser.cpp
	g++ -std=c++11 -I ./nodes -Werror  -pedantic-errors -g  -c -o lpl_parser.o lpl_parser.cpp


lpl_scanner.o: lpl_parser.o lpl_scanner.l
	flex --outfile=lpl_scanner.cpp --header-file=lpl_scanner.h lpl_scanner.l
	g++ -std=c++11 -I ./nodes -Werror  -pedantic-errors -g  -c -o lpl_scanner.o lpl_scanner.cpp



clean: 
	$(MAKE) -C nodes clean 
	rm -rf lpl_scanner.cpp lpl_scanner.h 
	rm -rf lpl_parser.cpp lpl_parser.h lpl_parser.out lpl_parser.o lpl_scanner.o
	rm -rf parser.o libparser.a
