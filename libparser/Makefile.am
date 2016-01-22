noinst_LIBRARIES = liblpl.a
liblpl_a_SOURCES =  lpl_scanner.l lpl_parser.y parser.c node.c
#liblpl_a_CPPFLAGS = -g -Werror -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition


lpl_parser.o: lpl_parser.y 
	lemon lpl_parser.y -s -p
	$(CC) $(CFLAGS) -c -o lpl_parser.o lpl_parser.c

#lpl_scanner.o: lpl_parser.o lpl_scanner.l
#	flex --outfile=lpl_scanner.c --header-file=lpl_scanner.h lpl_scanner.l
#	$(CC) $(CFLAGS) -c -o lpl_scanner.o lpl_scanner.c
 
parser.o: lpl_parser.o lpl_scanner.o parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

