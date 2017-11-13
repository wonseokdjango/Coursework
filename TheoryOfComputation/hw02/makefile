go : main.o Dict.o LZW.o
	g++ -std=c++11 -o go main.o Dict.o LZW.o
main.o : LZW.hpp main.cpp
	g++ -std=c++11 -c main.cpp
Dict.o : Types.hpp Dict.hpp Dict.cpp
	g++ -std=c++11 -c Dict.cpp
LZW.o : Types.hpp Dict.hpp LZW.hpp LZW.cpp
	g++ -std=c++11 -c LZW.cpp
clean :
	rm *.o go
