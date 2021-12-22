
#include <iostream>
#include "headers/tree.h"
#include <string>
using namespace std;

int main() {

    string boss = "Uspeshniq";
    string w1 = "Pesho";
    Tree<string> tree = Tree<string>(boss);
    tree.insertNode(w1, boss);

    tree.print();

    return 0;
}
