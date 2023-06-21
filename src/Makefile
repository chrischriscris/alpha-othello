CXX = g++
OPT = -Ofast -Wall -Wpedantic -std=c++11 -march=native -mtune=native

alpha-othello:	main.cpp othello_cut.hpp utils.hpp
	$(CXX) $(OPT) -o alpha-othello main.cpp

clean:
	rm -f alpha-othello
