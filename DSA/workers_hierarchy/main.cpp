
#include <iostream>
#include "headers/tree.h"
#include <string>
using namespace std;

int main() {

    string boss = "Uspeshniq";
    string w1 = "Pesho";
    string w2 = "Velin";
    string w3 = "Kiko";
    string w4 = "Wow";
    string w5 = "Nice";
    Tree<string> tree = Tree<string>(boss);

    tree.insertNode(w1, boss);
    tree.insertNode(w2, w1);
    tree.insertNode(w3, boss);
    tree.insertNode(w4, boss);
    tree.insertNode(w5, w4);

    tree.print();

    return 0;
}
