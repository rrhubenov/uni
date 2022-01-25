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
static const string TLBRACKET = "LBRACKET";
static const string TRBRACKET = "RBRACKET";
static const string TLSBRACKET = "LSBRACKET";
static const string TRSBRACKET = "RSBRACKET";

class Lexer {
    private:
        Token tokenizeReal(string::const_iterator& it) const;
    public:
        vector<Token> tokenize(const string input) const;
};
