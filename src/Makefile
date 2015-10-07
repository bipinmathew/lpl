all: export CXXFLAGS = -std=c++11 -pedantic-errors -O3
all: lpl tests


debug: export CXXFLAGS +=  -std=c++11 -pedantic-errors -g3 -DDEBUG
debug: lpl tests

lpl: libparser
	$(CXX)  $(CXXFLAGS) -static lpl.cpp -L parser -lparser -o lpl

tests: libparser
	$(MAKE) -C test all 

libparser:
	$(MAKE) -C parser libparser 


.PHONY: docs
docs:
	doxygen ./lpl_docs.config

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C test clean 
	$(MAKE) -C tip  clean
	rm -rf lpl ./docs/*
