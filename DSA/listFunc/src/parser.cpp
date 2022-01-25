#include "../headers/parser.hh"
#include "../headers/lexer.hh"

using namespace std;

NodeReal::NodeReal(string val) {
    this->val = stof(val);
}
NodeList::NodeList(vector<Node*> expressions): expressions(expressions) {}

string NodeReal::getType() {
    return "REAL";
}

string NodeList::getType() {
    return "LIST";
}

void Parser::next() {
    if(curr != tokens.cend()) {
        ++curr;
    } else {
        throw runtime_error("No more tokens");
    }
}
Node* Parser::parse_curr() {
    if(curr->name == TREAL || curr->name == TLBRACKET) {
        return parse_expression();
    } else {
        throw runtime_error("Not implemented yet");
    }
}

Node* Parser::parse(const vector<Token>& tokens) {
    Node* res = parse_expression();
    //TODO: If tokens remain -> return incorrect syntax error
    return res;
}

Node* Parser::parse_expression() {
    if(curr->name == TREAL) {
        return new NodeReal(curr->value);
    } else if(curr->name == TLSBRACKET) {
        vector<Node*> lexpr;
        next();
        while(curr->name != TRSBRACKET) {
            Node* n = parse_curr();
            lexpr.push_back(n);
            next();
        }
        return new NodeList(lexpr);
    }
}
