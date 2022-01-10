main: main.o hashmap.o comparator.o word_multiset.o
	g++ -g -o main -std=c++11 main.o hashmap.o comparator.o word_multiset.o

run: main
	./main

main.o:
	g++ -g -c -std=c++11 main.cpp -Wall -Werror -pedantic

comparator.o:
	g++ -g -c -std=c++11 src/comparator.cpp -Wall -Werror -pedantic

word_multiset.o:
	g++ -g -c -std=c++11 src/word_multiset.cpp -Wall -Werror -pedantic

hashmap.o:
	g++ -g -c -std=c++11 src/hashmap.cpp -Wall -Werror -pedantic

clean:
	rm *.o main runtests

runtests: tests
	./runtests

tests: test.o comparator.o word_multiset.o hashmap.o
	g++ -g -o runtests -std=c++11 test.o comparator.o word_multiset.o hashmap.o

test.o: 
	g++ -g -c -std=c++11 tests/test.cpp
