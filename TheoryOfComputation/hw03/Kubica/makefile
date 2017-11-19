go : main.o common.o
	g++ -std=c++11 -o go main.o common.o
main.o : common.hpp main.cpp
	g++ -std=c++11 -c main.cpp
common.o : common.hpp common.cpp
	g++ -std=c++11 -c common.cpp
clean :
	rm *.o go
