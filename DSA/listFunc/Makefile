
main: main.o lexer.o parser.o interpreter.o
	g++-11 -g -o main -std=c++11 main.o lexer.o parser.o interpreter.o -Wall -Werror -pedantic

main.o:
	g++-11 -g -c -std=c++11 main.cpp -Wall -Werror -pedantic

lexer.o:
	g++-11 -g -c -std=c++11 src/lexer.cpp -Wall -Werror -pedantic

parser.o:
	g++-11 -g -c -std=c++11 src/parser.cpp -Wall -Werror -pedantic

interpreter.o:
	g++-11 -g -c -std=c++11 src/interpreter.cpp -Wall -Werror -pedantic

clean:
	rm -f -- *.o main 