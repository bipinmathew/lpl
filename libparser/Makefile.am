SUBDIRS = libcol

BUILT_SOURCES = lpl_parser.c lpl_scanner.c arithmetic.c
AM_YFLAGS = -s -p
AM_LFLAGS =  --reentrant --header-file=lpl_scanner.h --outfile=lpl_scanner.c

arithmetic.c: arithmetic.tpl compile_arithmetic.awk
	$(AWK) -f compile_arithmetic.awk < arithmetic.tpl > arithmetic.c  

noinst_LIBRARIES = liblpl.a
liblpl_a_SOURCES =  lpl_scanner.l lpl_parser.y  parser.c node.c arithmetic.c
liblpl_a_CPPFLAGS = -I./libcol
liblpl_a_LIBADD = ./libcol/libcol.a
