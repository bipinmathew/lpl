SUBDIRS = libcol
SUBDIRS += c-algorithms

AM_YFLAGS = -s -p

arithmetic.c: arithmetic.inl dyadic.tpl compile_arithmetic.awk compile_arithmetic.awk arithmetic.tpl
	$(AWK) -f compile_arithmetic.awk < dyadic.tpl > arithmetic.c  
	./compile_arithmetic.sh arithmetic.tpl > arithmetic.inl 

logical.c: logical.inl dyadic.tpl compile_logical.awk compile_logical.awk logical.tpl
	$(AWK) -f compile_logical.awk < dyadic.tpl > logical.c  
	./compile_logical.sh logical.tpl > logical.inl 

noinst_LIBRARIES = liblpl.a
liblpl_a_SOURCES =  lpl_scanner.c lpl_parser.c parser.c node.c arithmetic.c logical.c
liblpl_a_CPPFLAGS = -I./libcol -I $(top_srcdir)/c-algorithms/src
BUILT_SOURCES = lpl_scanner.c lpl_scanner.h lpl_parser.c arithmetic.c logical.c
AM_LDFLAGS = -static 
liblpl_a_LIBADD = ./libcol/libcol.a
liblpl_a_LIBADD += -lfl 

lpl_scanner.h: lpl_scanner.l lpl_scanner.c
lpl_scanner.c: lpl_scanner.l 
	$(LEX) --reentrant --header-file=lpl_scanner.h --outfile=lpl_scanner.c lpl_scanner.l

lpl_parser.c: lpl_parser.y
	$(YACC) -s -p lpl_parser.y
