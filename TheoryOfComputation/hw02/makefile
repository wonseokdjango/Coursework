hw2 : main.o Trie.o LZW.o
	g++ -o hw2 main.o Trie.o LZW.o
main.o : LZW.hpp main.cpp
	g++ -c main.cpp
Trie.o : Trie.hpp Trie.cpp
	g++ -c Trie.cpp
LZW.o : Trie.hpp LZW.hpp LZW.cpp
	g++ -c LZW.cpp
clean :
	rm *.o hw2
