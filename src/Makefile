lpl: libparser 
	g++ -static lpl.cpp -pedantic-errors -g -L parser -lparser -o lpl

libparser:
	$(MAKE) -C parser libparser 

clean:
	$(MAKE) -C parser clean
	$(MAKE) -C tip  clean
	rm lpl
