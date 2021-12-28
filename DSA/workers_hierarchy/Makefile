main: hierarchy.o commands.o main.o 
	g++ -g -o main -std=c++11 hierarchy.o commands.o main.o

run: main
	./main

main.o: hierarchy.o
	g++ -g -c -std=c++11 main.cpp -Wall -Werror -pedantic

hierarchy.o:
	g++ -g -c -std=c++11 src/hierarchy.cpp -Wall -Werror -pedantic

commands.o:
	g++ -g -c -std=c++11 src/commands.cpp -Wall -Werror -pedantic

clean:
	rm *.o main runtests

runtests: tests
	./runtests

tests: hierarchy.o tests.o
	g++ -o runtests -std=c++11 hierarchy.o tests.o

tests.o:
	g++ -c -std=c++11 tests/tests.cpp
