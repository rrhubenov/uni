#include "headers/lexer.hh"
#include "headers/parser.hh"
#include <iostream>

using namespace std;

int main() {
    string line;
    Lexer l = Lexer();
    Parser p = Parser();

    while(getline(cin, line)) {
        vector<Token> ts = l.tokenize("[ 42.69 ] (())");
        Node* ast = p.parse(ts);
    }


    return 0;
}