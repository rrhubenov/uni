#include "../headers/interpreter.hh"


string Interpreter::eval(Node* ast) {
    Value* result = ast->eval();
    return result->print();
}