bin_PROGRAMS = lpl
lpl_SOURCES = lpl.c 

lpl_CPPFLAGS = -I$(top_srcdir)/libparser -I$(top_srcdir)/libparser/c-algorithms/src
lpl_LDFLAGS = -L ../libparser
lpl_LDFLAGS += -L ../libparser/c-algorithms/src/.libs
lpl_LDFLAGS += -L ../libparser/libcol
lpl_LDADD = -llpl 
lpl_LDADD += -lcalg 
lpl_LDADD += -lcol 
lpl_LDADD += -lrt
lpl_LDADD += -lfl
