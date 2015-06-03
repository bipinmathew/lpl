parser:
	lemon lpl_parser.y -s
	mv lpl_parser.c lpl_parser.cpp

scanner: lpl_scanner.l
	flex --outfile=lpl_scanner.cpp --header-file=lpl_scanner.h lpl_scanner.l

clean:
	rm -rf lpl_parser.c* lpl_parser.h* lpl_parser.out
	rm -rf lpl_scanner.cpp lpl_scanner.h
