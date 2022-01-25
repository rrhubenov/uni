
main: main.o lexer.o
	g++ -g -o main -std=c++11 main.o lexer.o -Wall -Werror -pedantic

main.o:
	g++ -g -c -std=c++11 main.cpp -Wall -Werror -pedantic

lexer.o:
	g++ -g -c -std=c++11 src/lexer.cpp -Wall -Werror -pedantic

clean:
	rm -f -- *.o main 