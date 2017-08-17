all: program1

program1: src/render.cpp
	g++ -std=c++11 src/render.cpp -o build/render
