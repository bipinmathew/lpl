all: export CXXFLAGS = -std=c++11 -pedantic-errors -O3
all: lpl docs


debug: export CXXFLAGS +=  -std=c++11 -pedantic-errors -g3 -DDEBUG
debug: lpl docs

lpl: libparser tests
	$(CXX)  $(CXXFLAGS) -static lpl.cpp -L parser -lparser -o lpl

libparser:
	$(MAKE) -C parser libparser 

tests:
	$(MAKE) -C test all 

.PHONY: docs
docs:
	doxygen ./lpl_docs.config

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C test clean 
	$(MAKE) -C tip  clean
	rm lpl
