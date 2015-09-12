all: test_lpl_arithmetic.cpp
	g++ -o test_lpl_arithmetic -I /usr/local/include -I ../ -L /usr/local/gtest test_lpl_arithmetic.cpp -L ../parser -lparser -L /usr/local/gtest -lgtest -lpthread

clean:
	rm test_lpl_arithmetic
