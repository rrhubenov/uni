#include "../headers/functions.hh"
#include <iostream>

Value *FuncEq::eval(unordered_map<string, Node*>& c) {
    Value* left = c.find("#0")->second->eval(c);
    Value* right = c.find("#1")->second->eval(c);

    if(left->compare(right)) {
        return new RealValue(1);
    } else {
        return new RealValue(0);
    }
}