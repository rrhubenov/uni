#pragma once
#include <vector>
#include "lexer.hh"

using namespace std;

class Value {
private:
    enum class Type {
        REAL,
        LIST
    };
    Type type;
public:
    virtual string print();
};

class RealValue: public Value {
private:
    float val;
public:
    RealValue(float val);

    float getValue();
    string print() override;
};
// class ListValue: public Value {
// public:
    // vector<Value> getValue();
// };

class Node {
private:
public:
    virtual Value* eval();
    virtual string print();
};

class ListNode: public Node {
private:
    vector<Node*> children;
public:
    ListNode(vector<Node*> children);
    string print() override;
    // Value eval() override;
};

class RealNode: public Node {
private:
    float val;
public:
    RealNode(float val);
    string print() override;
    Value* eval() override;
};

class FuncCallNode: public Node {
private:
    string id;
    vector<Node*> args;
public:
    FuncCallNode(string id, vector<Node*> args);
    string print() override;
};

class IntParamNode: public Node {
private:
    unsigned param;
public:
    IntParamNode(unsigned param);
    string print() override;
};

class FuncDecNode: public Node {
private:
    string id;
    Node* body;

public:
    FuncDecNode(string id, Node* body);
    string print() override;
};

class Parser {
private:
    vector<Token> tokens;
    vector<Token>::const_iterator curr;
    
    Node* parseList();
    Node* parseReal();
    Node* parseFuncDec();
    Node* parseFuncCall();
    Node* parseIntParam();

    vector<Token>::const_iterator peek();
    vector<Token>::const_iterator next();

public:
    Parser(const vector<Token>& tokens);
    Node* parse();
};


