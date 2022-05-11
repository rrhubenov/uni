#pragma once
#include <vector>
#include <unordered_map>
#include "lexer.hh"

using namespace std;

class Value {
public:
    enum class Type {
        REAL,
        LIST
    };
    Type type;
    virtual string print();
    virtual bool compare(Value* other);
    virtual Type getType();
};

class RealValue: public Value {
private:
    float val;
public:
    RealValue(float val);

    float getValue();
    string print() override;
    bool compare(Value* other) override;
    Type getType() override;
};
class ListValue: public Value {
private:
    vector<Value*> vals;
public:
    ListValue(vector<Value*> vals);

    vector<Value*> getValue();
    string print() override;
    bool compare(Value* other) override;
    Type getType() override;
};

class Node {
private:
public:
    virtual Value* eval(unordered_map<string, Node*>& _);
    virtual string print();
};

class ListNode: public Node {
private:
    vector<Node*> children;
public:
    ListNode(vector<Node*> children);
    string print() override;
    Value* eval(unordered_map<string, Node*>& c) override;
};

class RealNode: public Node {
private:
    float val;
public:
    RealNode(float val);
    string print() override;
    Value* eval(unordered_map<string, Node*>& _) override;
};

class FuncCallNode: public Node {
private:
    string id;
    vector<Node*> args;
public:
    FuncCallNode(string id, vector<Node*> args);
    string print() override;

    Value *eval(unordered_map<string, Node*>& c);
};

class IntParamNode: public Node {
private:
    unsigned param;
public:
    IntParamNode(unsigned param);
    string print() override;

    Value *eval(unordered_map<string, Node*>& c);
};

class FuncDecNode: public Node {
private:
    string id;
    Node* body;

public:
    FuncDecNode(string id, Node* body);
    string print() override;

    Value* eval(unordered_map<string, Node*>& c);
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


