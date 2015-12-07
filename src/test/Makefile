all: arithmetic memchk

memchk:
	g++ -g -DDEBUG -o lpl_memchk -I /usr/local/include -I ../parser -L /usr/local/gtest lpl_memchk.cpp -L ../parser -llpl -L /usr/local/gtest -lgtest -lpthread

arithmetic: test_lpl_arithmetic.cpp
	g++ -c -o test_lpl_arithmetic.o -I /usr/local/include -I ../parser test_lpl_arithmetic.cpp 
	g++ -o test_lpl_arithmetic -L /usr/local/gtest -L../parser -L /usr/local/gtest test_lpl_arithmetic.o -lgtest -lpthread -llpl 

clean:
	rm test_lpl_arithmetic lpl_memchk
