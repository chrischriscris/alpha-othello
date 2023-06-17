CXX = g++
OPT = -Ofast -Wall -Wpedantic -std=c++17 -march=native -mtune=native

main:	main.cc othello_cut.h
	$(CXX) $(OPT) -o main main.cpp

clean:
	rm -f main core *~
