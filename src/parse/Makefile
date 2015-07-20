parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	gcc -Werror  -pedantic-errors -g -c -o lpl_parser.o lpl_parser.c


scanner.o: lpl_scanner.l
	flex --outfile=lpl_scanner.c --header-file=lpl_scanner.h lpl_scanner.l
	gcc -Werror  -pedantic-errors -g -c -o lpl_scanner.o lpl_scanner.c

all: parser.o scanner.o
