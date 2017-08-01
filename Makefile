all: program1

program1: src/background.cpp
	g++ -std=c++11 src/background.cpp -o build/background
