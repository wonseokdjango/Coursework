all : hw1 checker

hw1 : hw1.o
	g++ -std=c++11 -o hw1 hw1.o
checker : checker.o
	g++ -std=c++11 -o checker checker.o

hw1.o : hw1.cpp
	g++ -std=c++11 -c hw1.cpp
checker.o : checker.cpp
	g++ -std=c++11 -c checker.cpp

clean :
	rm *.o hw1 checker
