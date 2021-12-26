
#include <iostream>
#include "headers/tree.h"
#include <string>
using namespace std;

int main() {

    string boss = "Uspeshnia";
    string w1 = "Gosho";
    string w2 = "Misho";
    string w3 = "Slavi";
    string w4 = "Dancho";
    string w5 = "Pesho";
    string w6 = "Slav1";
    string w7 = "Slav2";
    Tree<string> tree = Tree<string>(boss, nullptr);

    tree.insertNode(w2, boss);
    tree.insertNode(w1, boss);
    tree.insertNode(w3, boss);
    tree.insertNode(w4, w1);
    tree.insertNode(w5, w1);
    tree.insertNode(w7, w3);
    tree.insertNode(w6, w3);

    // tree.remove(w1);

    tree.print();

    return 0;
}
