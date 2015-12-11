lpl_parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	$(CC) $(CFLAGS) -c -o lpl_parser.o lpl_parser.c


lpl_scanner.o: lpl_parser.o lpl_scanner.l
	flex --outfile=lpl_scanner.c --header-file=lpl_scanner.h lpl_scanner.l
	$(CC) $(CFLAGS) -c -o lpl_scanner.o lpl_scanner.c

parser.o: lpl_parser.o lpl_scanner.o parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

node.o:
	$(MAKE) -C nodes 


liblpl: lpl_parser.o lpl_scanner.o node.o parser.o
	ar rc liblpl.a lpl_parser.o lpl_scanner.o nodes/node.o parser.o


all: liblpl

clean: 
	$(MAKE) -C nodes clean 
	rm -rf lpl_scanner.c lpl_scanner.h 
	rm -rf lpl_parser.c lpl_parser.h 
	rm -rf lpl_lpl_scanner.o lpl_parser.o  
	rm -rf parser.o  
	rm -rf liblpl.a
