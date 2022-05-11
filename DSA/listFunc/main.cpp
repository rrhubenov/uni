#include "headers/parser.hh"
#include "headers/lexer.hh"
#include "headers/interpreter.hh"
#include "headers/functions.hh"

#include <unordered_map>
#include <iostream>

using namespace std;

void addSystemFunctions(unordered_map<string, Node*>& c) {
    c.insert(make_pair("eq", new FuncEq));
}


int main() {
    unordered_map<string, Node*> c;

    addSystemFunctions(c);

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
        cout << i.eval(n, c) << endl;

        cout << "> ";
    }


    return 0;
}