#include "parser.hh"

class FuncEq: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncLessThan: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncNand: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncLength: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncHead: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncTail: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncList: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncConcat: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncIf: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncRead: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncWrite: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncInt: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};

class FuncAdd: public Node {
public:
    Value *eval(unordered_map<string, Node*>& c);
};
