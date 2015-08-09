node.o: node.h node.cpp
	g++ -Werror  -pedantic-errors -g -c -o node.o node.cpp

intNode.o: node.h intNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o intNode.o intNode.cpp


doubleNode.o: node.h doubleNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o doubleNode.o doubleNode.cpp


errorNode.o: node.h errorNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o errorNode.o errorNode.cpp


addNode.o: node.h addNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o addNode.o addNode.cpp


all: node.o intNode.o doubleNode.o errorNode.o addNode.o

clean:
	rm -rf *.o
