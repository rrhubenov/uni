#include "headers/hashmap.h"
#include "headers/interface.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std; 

int main(int argc, char** argv) {
    if(argc != 3) {
        cerr << "ERROR: Program requires 2 positional arguments: <file1> <file2> " << endl;
    }

    string f1Name = argv[1];
    string f2Name = argv[2];

    ifstream f1 = ifstream(f1Name);
    ifstream f2 = ifstream(f2Name);

    if(f1.fail()) {
        cerr << "ERROR: file \"" << f1Name << "\" not found." << endl;
        exit(1);
    }
    if(f2.fail()) {
        cerr << "ERROR: file \"" << f2Name << "\" not found." << endl;
        exit(1);
    }

    Comparator c;
    ComparisonReport cr = c.compare(f1,f2);

    size_t f1Size = cr.uniqueWords[0].countOfAllWords() + cr.commonWords.countOfAllWords();
    size_t f2Size = cr.uniqueWords[1].countOfAllWords() + cr.commonWords.countOfAllWords();

    cout << f1Name << " has " << f1Size <<  " words and " << cr.commonWords.countOfAllWords() << " are contained in " << f2Name << endl;
    cout << f2Name << " has " << f2Size <<  " words and " << cr.commonWords.countOfAllWords() << " are contained in " << f1Name << endl;

    return 0;
}


