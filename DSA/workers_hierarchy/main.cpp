
#include <iostream>
#include <fstream>
#include "headers/interface.h"
#include <string>
#include <vector>
using namespace std;

vector<Hierarchy> hierarchies;

int main() {
    string command;
    cin >> command;
    if(command == "load") {
        string fName;
        string hName;

        cin >> hName >> fName;

        fstream file;
        string buffer;

        file.open("input", ios::in);

        if(file.is_open()) {
            string line;
            while(getline(file, line)) {
                buffer += line;
                buffer += "\n";
            }

            file.close();
            Hierarchy h = Hierarchy(buffer);
            hierarchies.push_back(h);
            cout << hierarchies[0].print();
        } else {
            cout << "File was not opened" << endl;
        }

    } else {
        cout << "unknown command" << endl;
    }


    return 0;
}
