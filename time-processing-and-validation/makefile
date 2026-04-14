all: main
main: clockexcept clock main.cpp
	g++ -pedantic-errors -g main.cpp clock clockexcept -o main
clock: clock.cpp clock.h
	g++ -pedantic-errors -g -c clock.cpp -o clock
clockexcept: clockexcept.h clockexcept.cpp
	g++ -pedantic-errors -g -c clockexcept.cpp -o clockexcept