all: export CXXFLAGS = -std=c++11 -pedantic-errors -O3
all: lpl


debug: export CXXFLAGS +=  -std=c++11 -pedantic-errors -g3 -DDEBUG
debug: lpl

lpl: libparser 
	$(CXX)  $(CXXFLAGS) -static lpl.cpp -L parser -lparser -o lpl

libparser:
	$(MAKE) -C parser libparser 

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C tip  clean
	rm lpl
