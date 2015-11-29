parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	$(CC) $(CFLAGS) -c -o lpl_parser.o lpl_parser.c


scanner.o: lpl_scanner.l
	flex --outfile=lpl_scanner.c --header-file=lpl_scanner.h lpl_scanner.l
	$(CC) $(CFLAGS) -c -o lpl_scanner.o lpl_scanner.c

node.o:
	$(MAKE) -C nodes 


liblpl: parser.o scanner.o node.o
	ar rc liblpl.a lpl_parser.o lpl_scanner.o nodes/node.o
	ranlib liblpl.a


all: liblpl

clean: 
	$(MAKE) -C nodes clean 
	rm -rf lpl_scanner.c lpl_scanner.h 
	rm -rf lpl_parser.c lpl_parser.h 
	rm -rf lpl_scanner.o lpl_parser.o  
	rm -rf liblpl.a
