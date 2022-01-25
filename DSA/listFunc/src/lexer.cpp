#include "../headers/lexer.hh"
#include <vector>
using namespace std;

char digits[] = {'0','1','2','3','4','5','6','7','8','9'};

static bool contains(const char elem, const char* elems, const size_t size) {
    for(size_t i = 0; i < size; ++i) {
        if(elems[i] == elem) {
            return true;
        }
    }
    return false;
}

vector<Token> Lexer::tokenize(const string input) const {
    vector<Token> result;

    for(string::const_iterator it = input.cbegin(); it != input.cend(); ++it) {
        if(*it == ' ') {
            continue;
        }else if(contains(*it, digits, 10)) {
            result.push_back(tokenizeReal(it));
        } else if(*it == '(') {
            result.push_back(Token {LBRACKET, "("});
        } else if(*it == ')') {
            result.push_back(Token {RBRACKET, ")"});
        } else if(*it == '[') {
            result.push_back(Token {LSBRACKET, "["});
        } else if(*it == ']') {
            result.push_back(Token {RSBRACKET, "]"});
        } else {
            // TODO: Custom Lexer error
            throw runtime_error("Unknown token");
        }
    }

    return result;
}

Token Lexer::tokenizeReal(string::const_iterator& it) const {
    string result = "";
    bool isFloat = false;
    while(*it != ' ') {
        if(*it == '.') {
            if(isFloat) {
                throw runtime_error("Floats must have one floating point");
            } else {
                isFloat = true;
            }
            result.push_back(*it);
        } else if(contains(*it, digits, 10)) {
            result.push_back(*it);
        }else {
            throw runtime_error("Could not parse real number");
        }
        ++it;
    }

    return Token {TREAL, result};
}

