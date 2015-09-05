lpl: libparser 
	g++ -static lpl.cpp -pedantic-errors -g -L parse -lparser -o lpl

libparser:
	$(MAKE) -C parse libparser 

clean:
	$(MAKE) -C parse clean
	$(MAKE) -C tip  clean
	rm lpl.o lpl
