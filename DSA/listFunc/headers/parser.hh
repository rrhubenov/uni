#pragma once
#include <vector>
#include "lexer.hh"

using namespace std;


class Node {
    public:
        virtual string getType();
};

class NodeReal : public Node {
private:
    double val;
    string getType();
public:
    NodeReal(string val);
};

class NodeList : public Node {
private:
    vector<Node*> expressions;
    string getType();
public:
    NodeList(vector<Node*> expressions);
};


class Parser {
private:
    vector<Token> tokens;
    vector<Token>::const_iterator curr;
    
    void next();
    Node* parse_expression();

    Node* parse_curr();

public:
    Node* parse(const vector<Token>& tokens);

};


