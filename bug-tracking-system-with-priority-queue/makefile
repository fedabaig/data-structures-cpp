all: BugReport.o
	g++ -pedantic-errors main.cpp BugReport.o -g -o main
BugReport.o: BugReport.h BugReport.cpp
	g++ -pedantic-errors BugReport.cpp -g -o BugReport.o -c
