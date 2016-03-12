SUBDIRS = libcol

BUILT_SOURCES = lpl_parser.c lpl_parser.h lpl_scanner.h arithmetic.c
AM_YFLAGS = -s -p
AM_LFLAGS = --header-file=lpl_scanner.h

arithmetic.c: arithmetic.tpl compile_arithmetic.awk
	$(AWK) -f compile_arithmetic.awk < arithmetic.tpl > arithmetic.c  

noinst_LIBRARIES = liblpl.a
liblpl_a_SOURCES =  lpl_parser.y lpl_scanner.l parser.c node.c arithmetic.c
liblpl_a_CPPFLAGS = -I./libcol
liblpl_a_LIBADD = ./libcol/libcol.a
