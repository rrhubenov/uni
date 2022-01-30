#include "../headers/parser.hh"
#include "../headers/lexer.hh"
#include <iostream>

#include <cassert>

using namespace std;

///////////////// Values

string Value::print() {
    return "Default val";
}

RealValue::RealValue(float val): val(val) {}
float RealValue::getValue() {
    return val;
}

string RealValue::print() {
    return to_string(val);
}

/////////////// Nodes

string Node::print() {
    return "Something went wrong";
}
Value* Node::eval() {
    return new RealValue(-999);
}

RealNode::RealNode(float val):  val(val) {}

string RealNode::print() {
    // TODO: Print to the 2nd decimal point
    return to_string(val);
}

Value* RealNode::eval() {
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

FuncCallNode::FuncCallNode(string id, vector<Node*> args): id(id), args(args) {}

string FuncCallNode::print() {
    string res = "<function " + id + ", args: ";
    for(vector<Node*>::iterator it = args.begin(); it != args.end(); ++it) {
        res.append((*it)->print() + " ");
    }

    res.append(">");
    return res;
}

IntParamNode::IntParamNode(unsigned param): param(param) {}
string IntParamNode::print() {
    return "#" + to_string(param);
}

FuncDecNode::FuncDecNode(string id, Node* body): id(id), body(body) {}
string FuncDecNode::print() {
    return "<function " + id + " body: " + body->print() + ">";
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
