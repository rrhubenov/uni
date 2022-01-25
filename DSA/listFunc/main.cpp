#include "headers/lexer.hh"
#include <iostream>

using namespace std;

int main() {

    Lexer l = Lexer();

    vector<Token> ts = l.tokenize("[ 42.69 ] (())");

    for(auto t : ts) {
        cout << t.name << " " << t.value << endl;
    }

    return 0;
}