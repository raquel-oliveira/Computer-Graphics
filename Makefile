all: program1 program2

program1: src/backgroundP3.cpp
	g++ -std=c++11 src/backgroundP3.cpp -o build/backgroundP3
program2: src/backgroundP3.cpp
	g++ -std=c++11 src/backgroundP6.cpp -o build/backgroundP6
