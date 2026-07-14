all: compile execute

compile:
	g++ *.cpp -o main.exe -std=c++11

execute:
	./main.exe