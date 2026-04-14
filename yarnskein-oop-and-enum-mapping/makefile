all: yarn
	g++ -pedantic-errors -fdiagnostics-color=always -g main.cpp yarn -o main
yarn: yarn.h yarn.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g -c yarn.cpp -o yarn
