go : main.o Dict.o LZW.o
	g++ -o go main.o Dict.o LZW.o
main.o : LZW.hpp main.cpp
	g++ -c main.cpp
Dict.o : Types.hpp Dict.hpp Dict.cpp
	g++ -c Dict.cpp
LZW.o : Types.hpp Dict.hpp LZW.hpp LZW.cpp
	g++ -c LZW.cpp
clean :
	rm *.o go
