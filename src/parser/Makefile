parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	gcc -Werror  -pedantic-errors -c -o lpl_parser.o lpl_parser.c


scanner.o: lpl_scanner.l
	flex --outfile=lpl_scanner.c --header-file=lpl_scanner.h lpl_scanner.l
	gcc -Werror  -pedantic-errors -c -o lpl_scanner.o lpl_scanner.c

node.o:
	$(MAKE) -C nodes 


liblpl: parser.o scanner.o node.o
	ar rc liblpl.a lpl_parser.o lpl_scanner.o nodes/node.o
	ranlib liblpl.a


all: liblpl

clean: 
	rm -rf lpl_scanner.c lpl_scanner.h 
	rm -rf lpl_parser.c lpl_parser.h 
	rm -rf lpl_scanner.o lpl_parser.o  
	rm -rf liblpl.a
