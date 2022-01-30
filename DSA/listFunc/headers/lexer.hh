#pragma once
#include <string>
#include <vector>

/*
    Literal = RealNum
    Identifier = String
    ScopeBounders = LBracket | RBracket | LSBracket | RSBracket
*/


using namespace std;

struct Token {
    enum class Type {
        REAL,
        BRACKET_L,
        BRACKET_R,
        SBRACKET_L,
        SBRACKET_R,
        ARROW,
        ID,
        COMMA,
        ARG
    };
    Type type;
    string value;

    string print();
};

class Lexer {
    private:
        Token tokenizeArrowOrReal(string::const_iterator& it) const;
        Token tokenizeReal(string::const_iterator& it) const;
        Token tokenizeId(string::const_iterator& it) const;
    public:
        vector<Token> tokenize(const string input) const;
};
