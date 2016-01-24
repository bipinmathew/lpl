SUBDIRS = libcol

noinst_LIBRARIES = liblpl.a
liblpl_a_SOURCES =  lpl_parser.c lpl_scanner.l parser.c node.c
liblpl_a_DEPENDENCIES = lpl_parser 
liblpl_a_CPPFLAGS = -I./libcol
liblpl_a_LIBADD = ./libcol/libcol.a

lpl_parser: lpl_parser.y 
	$(YACC) lpl_parser.y -s -p
