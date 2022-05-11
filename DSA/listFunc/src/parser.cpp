#include "../headers/parser.hh"
#include "../headers/lexer.hh"
#include <iostream>

#include <cassert>

using namespace std;

///////////////// Values

string Value::print() {
    return "Default val";
}

bool Value::compare(Value* other) {
    return false;
}

Value::Type Value::getType() {
    return Type::REAL;
}

RealValue::RealValue(float val): val(val) {}
float RealValue::getValue() {
    return val;
}

string RealValue::print() {
    return to_string(val);
}

Value::Type RealValue::getType() {
    return Value::Type::REAL;
}

bool RealValue::compare(Value* other) {
    if(other->getType() != Value::Type::REAL) {
        return false;
    } else {
        RealValue* cother = static_cast<RealValue*>(other);
        return this->val == cother->val;
    }
}

ListValue::ListValue(vector<Value*> vals): vals(vals) {}
vector<Value*> ListValue::getValue() {
    return vals;
}

Value::Type ListValue::getType() {
    return Value::Type::LIST;
}

string ListValue::print() {
    string res = "[ ";

    for(vector<Value*>::iterator it = vals.begin(); it != vals.end(); ++it) {
        res.append((*it)->print() + " ");
    }

    res.append(" ]");
    return res;
}

bool ListValue::compare(Value* other) {
    if(other->getType() != Value::Type::LIST) {
        return false;
    } else {
        ListValue* cother = static_cast<ListValue*>(other);
        if(cother->vals.size() != this->vals.size()) {
            return false;
        } else {
            size_t index = 0;
            for(vector<Value*>::iterator it = vals.begin(); it != vals.end(); ++it) {
                if(!(*it)->compare(cother->vals[index])) {
                    return false;
                }
                index++;
            }
            return true;
        }
    }
}

/////////////// Nodes

string Node::print() {
    return "Something went wrong";
}
Value* Node::eval(unordered_map<string, Node*>& _) {
    return new RealValue(-999);
}

RealNode::RealNode(float val):  val(val) {}

string RealNode::print() {
    // TODO: Print to the 2nd decimal point
    return to_string(val);
}

Value* RealNode::eval(unordered_map<string, Node*>& _) {
    return new RealValue(val);
}

ListNode::ListNode(vector<Node*> children): children(children) {}

string ListNode::print() {
    string result = "( ";
    for(vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        result.append((*it)->print() + " ");
    }

    result.append(")");

    return result;
}

Value* ListNode::eval(unordered_map<string, Node*>& c) {
    vector<Value*> vals;

    for(vector<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
        vals.push_back((*it)->eval(c));
    }

    return new ListValue(vals);
}

FuncCallNode::FuncCallNode(string id, vector<Node*> args): id(id), args(args) {}

string FuncCallNode::print() {
    string res = "<function " + id + ", args: ";
    for(vector<Node*>::iterator it = args.begin(); it != args.end(); ++it) {
        res.append((*it)->print() + " ");
    }

    res.append(">");
    return res;
}

Value* FuncCallNode::eval(unordered_map<string, Node*>& c) {
    unordered_map<string, Node*>::iterator funcit = c.find(id);

    if(funcit == c.end()) {
        throw "not found error";
    } 

    Node* func = funcit->second;

    for(size_t i = 0; i < args.size(); ++i) {
        c.insert(make_pair("#" + to_string(i), args[i]));
    }

    Value* result = func->eval(c);

    for(size_t i = 0; i < args.size(); ++i) {
        c.erase("#" + to_string(i));
    }

    return result;
}

IntParamNode::IntParamNode(unsigned param): param(param) {}
string IntParamNode::print() {
    return "#" + to_string(param);
}

Value* IntParamNode::eval(unordered_map<string, Node*>& c) {
    unordered_map<string, Node*>::iterator val = c.find("#" + to_string(param));

    if(val == c.end()) {
        throw "param " + to_string(param) + " not found";
    }

    return val->second->eval(c);
}

FuncDecNode::FuncDecNode(string id, Node* body): id(id), body(body) {}
string FuncDecNode::print() {
    return "<function " + id + " body: " + body->print() + ">";
}

Value* FuncDecNode::eval(unordered_map<string, Node*>& c) {
    unsigned exists = c.find(id) == c.end() ? 0 : 1;

    c.insert(make_pair(id, body));

    return new RealValue(exists);
}

//////////////////// Parser

Node* Parser::parseReal() {
    return new RealNode(stof(curr->value));
}

Parser::Parser(const vector<Token>& tokens): tokens(tokens), curr(tokens.begin()) {}

vector<Token>::const_iterator Parser::peek() {
    vector<Token>::const_iterator peeked = ++curr;
    --curr;
    return peeked;
}

vector<Token>::const_iterator Parser::next() {
    return ++curr;
}

Node* Parser::parseList() {
    vector<Node*> children;

    next();
    while(curr->type != Token::Type::SBRACKET_R) {
        children.push_back(parse());
    }
    next();

    return new ListNode(children);
}

Node* Parser::parseFuncCall() {
    vector<Node*> args;
    string id = curr->value;

    next();
    next();
    while(curr->type != Token::Type::BRACKET_R) {
        args.push_back(parse());
        if(curr->type == Token::Type::COMMA) next();
    }
    next();

    return new FuncCallNode(id, args);
}

Node* Parser::parseIntParam() {
    return new IntParamNode(stof(curr->value));
}

Node* Parser::parseFuncDec() {
    string id = curr->value;
    next();
    next();
    Node* body = parse();

    return new FuncDecNode(id, body);
}

Node* Parser::parse() {
    Node* n;
    if(curr->type == Token::Type::ID) {
        if(peek()->type == Token::Type::ARROW) {
            n = parseFuncDec();
        } else if(peek()->type == Token::Type::BRACKET_L) {
            n = parseFuncCall();
        }  else {
            // TODO: Throw better errors
            throw "Syntax error";
        }
    } else if(curr->type == Token::Type::REAL) {
        n = parseReal();
        next();
    } else if(curr->type == Token::Type::SBRACKET_L) {
        n = parseList();
    } else if(curr->type == Token::Type::ARG) {
        n = parseIntParam();
        next();
    } else {
        // syntax error
        throw "Syntax error";
    }

    return n;
}
