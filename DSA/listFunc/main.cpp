#include "headers/parser.hh"
#include "headers/lexer.hh"
#include "headers/interpreter.hh"
#include <iostream>

using namespace std;

int main() {
    string line;
    Lexer l;
    Interpreter i;

    cout << "> ";
    while(getline(cin, line)) {
        // Used to determine end of line
        // Dirty hack, needs to be reworked
        line = line + ' ';
        vector<Token> ts = l.tokenize(line);
        Parser p(ts);

        Node* n = p.parse();
        cout << i.eval(n) << endl;

        cout << "> ";
    }


    return 0;
}