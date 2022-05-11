#pragma once
#include "parser.hh"
#include <unordered_map>
#include <vector>

using namespace std;

class Interpreter {

public:
    string eval(Node* ast, unordered_map<string, Node*>& c);
};
