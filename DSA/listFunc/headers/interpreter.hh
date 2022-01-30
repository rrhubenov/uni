#pragma once
#include "parser.hh"
#include <vector>

using namespace std;

class Interpreter {

public:
    string eval(Node* ast);
};
