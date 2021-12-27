
#include <iostream>
#include "headers/interface.h"
#include <string>
using namespace std;

const string lozenec =
    "Uspeshnia - Gosho \n"
    "Uspeshnia - Misho \n"
    "Gosho     - Pesho \n"
    "Gosho     - Dancho\n"
    "Pesho     - Alex  \n"
    "Dancho    - Boris \n"
    "Dancho    - Kamen \n"
    "Uspeshnia - Slavi \n"
    "Slavi     - Slav1 \n"
    "Slavi     - Slav2 \n"
    "Slav1     - Mecho \n"
    "Mecho     - Q12Adl\n";

const string loz_new =
    " Uspeshnia   -  MishoPetrov \n"
    " MishoPetrov -  Misho       \n"
    " MishoPetrov -  Slav        \n";

int main() {
    Hierarchy h1 = Hierarchy(lozenec);
    Hierarchy h2 = Hierarchy(loz_new);

    Hierarchy joined = h2.join(h1);

    cout << joined.print() << endl;

    return 0;
}
