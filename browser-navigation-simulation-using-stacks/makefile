all: url main
main: url main.cpp
	g++ -pedantic-errors -g main.cpp url -o main
	#for msys/mingw first run pacman -Sy mingw-w64-i686-gcc mingw-w64-i686-headers-git
	#then swap the compile command for the one commented out below
	#g++ -pedantic-errors -g main.cpp url -lws2_32 -o main
url: url.h url.cpp
	g++ -pedantic-errors -g -c url.cpp -o url
	