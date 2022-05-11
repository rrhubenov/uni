#include "../headers/interpreter.hh"
#include "../headers/parser.hh"
#include <unordered_map>


string Interpreter::eval(Node* ast, unordered_map<string, Node*>& c) {
    Value* result = ast->eval(c);
    return result->print();
}