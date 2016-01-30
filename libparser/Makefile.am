SUBDIRS = libcol

BUILT_SOURCES = lpl_parser.c lpl_parser.h lpl_scanner.h
AM_YFLAGS = -s -p
AM_LFLAGS = --header-file=lpl_scanner.h

noinst_LIBRARIES = liblpl.a
liblpl_a_SOURCES =  lpl_parser.y lpl_scanner.l parser.c node.c
liblpl_a_CPPFLAGS = -I./libcol
liblpl_a_LIBADD = ./libcol/libcol.a
