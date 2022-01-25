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
    string name;
    string value;
};

static const string TREAL = "REAL";
static const string LBRACKET = "LBRACKET";
static const string RBRACKET = "RBRACKET";
static const string LSBRACKET = "LSBRACKET";
static const string RSBRACKET = "RSBRACKET";

class Lexer {
    private:
        Token tokenizeReal(string::const_iterator& it) const;
    public:
        vector<Token> tokenize(const string input) const;
};
