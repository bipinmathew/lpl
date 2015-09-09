node.o: node.h node.cpp
	$(CXX) $(CXXFLAGS)   -c -o node.o node.cpp

intNode.o: node.h intNode.cpp
	$(CXX) $(CXXFLAGS)   -c -o intNode.o intNode.cpp


doubleNode.o: node.h doubleNode.cpp
	$(CXX) $(CXXFLAGS)   -c -o doubleNode.o doubleNode.cpp


addNode.o: node.h addNode.cpp
	$(CXX) $(CXXFLAGS)   -c -o addNode.o addNode.cpp


subNode.o: node.h subNode.cpp
	$(CXX) $(CXXFLAGS)   -c -o subNode.o subNode.cpp


divNode.o: node.h divNode.cpp
	$(CXX) $(CXXFLAGS)   -c -o divNode.o divNode.cpp


multNode.o: node.h multNode.cpp
	$(CXX) $(CXXFLAGS)   -c -o multNode.o multNode.cpp


visitors.o: visitors.h node.h visitors.cpp
	$(CXX) $(CXXFLAGS)   -c -o visitors.o visitors.cpp

all: node.o intNode.o doubleNode.o addNode.o subNode.o divNode.o multNode.o visitors.o

clean:
	rm -rf *.o
