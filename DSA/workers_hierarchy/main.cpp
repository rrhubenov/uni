
#include <iostream>
#include "headers/interface.h"
#include <string>
using namespace std;

int main() {
    string input = string("Uspeshnia-Gosho\nUspeshnia-Misho\nUspeshnia-Slavi\nGosho-Dancho\nGosho-Pesho\n");
    Hierarchy h1 = Hierarchy(input);

    cout << h1.print();
    cout << h1.longest_chain();

    return 0;
}
