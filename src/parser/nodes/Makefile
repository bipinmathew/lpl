node.o: node.h node.cpp
	g++ -Werror  -pedantic-errors -g -c -o node.o node.cpp

intNode.o: node.h intNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o intNode.o intNode.cpp


doubleNode.o: node.h doubleNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o doubleNode.o doubleNode.cpp


addNode.o: node.h addNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o addNode.o addNode.cpp


subNode.o: node.h subNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o subNode.o subNode.cpp


divNode.o: node.h divNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o divNode.o divNode.cpp


multNode.o: node.h multNode.cpp
	g++ -Werror  -pedantic-errors -g -c -o multNode.o multNode.cpp


visitors.o: visitors.h node.h visitors.cpp
	g++ -Werror  -pedantic-errors -g -c -o visitors.o visitors.cpp

all: node.o intNode.o doubleNode.o addNode.o subNode.o divNode.o multNode.o visitors.o

clean:
	rm -rf *.o
