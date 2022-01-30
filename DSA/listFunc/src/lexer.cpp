#include "../headers/lexer.hh"
#include <vector>
using namespace std;

char digits[] = {'0','1','2','3','4','5','6','7','8','9'};

string Token::print() {
    switch(type) {
        case Type::REAL:
        case Type::ID:
        case Type::ARG:
            return "{ " + value + " }";
        case Type::BRACKET_L:
            return  "{ ( }";
        case Type::BRACKET_R:
            return "{ ) }";
        case Type::SBRACKET_L:
            return "{ [ }";
        case Type::SBRACKET_R:
            return "{ ] }";
        case Type::ARROW:
            return "{ -> }";
        case Type::COMMA:
            return "{ , }";
        default:
            return "{ unrecognized }";
    }
}

static bool contains(const char elem, const char* elems, const size_t size) {
    for(size_t i = 0; i < size; ++i) {
        if(elems[i] == elem) {
            return true;
        }
    }
    return false;
}

Token Lexer::tokenizeReal(string::const_iterator& it) const {
    string result = "";
    bool isFloat = false;
    while(contains(*it, digits, 10) || *it == '.') {
        if(*it == '.') {
            if(isFloat) {
                throw "Floats must have one floating point";
            } else {
                isFloat = true;
            }
            result.push_back(*it);
        } else if(contains(*it, digits, 10)) {
            result.push_back(*it);
        }else {
            throw "Could not parse real number";
        }
        ++it;
    }
    --it;

    return Token {Token::Type::REAL, result};
}

Token Lexer::tokenizeArrowOrReal(string::const_iterator& it) const {
    ++it;
    if(*it == '>') {
        return Token { Token::Type::ARROW, "->" };
    } else if(contains(*it, digits, 10)) {
        Token real = tokenizeReal(it);
        return Token { Token::Type::REAL, "-" + real.value };
    } else {
        throw "Unrecognized symbol after -";
    }
}

Token Lexer::tokenizeId(string::const_iterator& it) const {
    char nonSymbols[] = { ',', ' ', '>', '-', '[', ']', '{', '}', '(', ')'};
    string result = "";
    while(!contains(*it, nonSymbols, 10)) {
        result.push_back(*it);
        ++it;
    }
    --it;

    return Token {Token::Type::ID, result};
}

vector<Token> Lexer::tokenize(const string input) const {
    vector<Token> result;

    for(string::const_iterator it = input.cbegin(); it != input.cend(); ++it) {

        switch(*it) {
            case ' ':
            case '\t':
            case '\n':
                continue;
            default:
                break;
        }

        if(contains(*it, digits, 10)) {
            result.push_back(tokenizeReal(it));
        } else if(*it == '(') {
            result.push_back(Token {Token::Type::BRACKET_L, "("});
        } else if(*it == ')') {
            result.push_back(Token {Token::Type::BRACKET_R, ")"});
        } else if(*it == '[') {
            result.push_back(Token {Token::Type::SBRACKET_L, "["});
        } else if(*it == ']') {
            result.push_back(Token {Token::Type::SBRACKET_R, "]"});
        } else if(*it == '-') {
            result.push_back(tokenizeArrowOrReal(it));
        } else if(*it == ',') {
            result.push_back(Token {Token::Type::COMMA, ","});
        } else if(*it == '#') {
            Token real = tokenizeReal(++it);
            result.push_back(Token {Token::Type::ARG, real.value});
        } else {
            result.push_back(tokenizeId(it));
        }
    }

    return result;
}
