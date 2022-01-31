// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// 
// Курсове Структури от данни и програмиране
//         Структури от данни
// Зимен семестър 2021/22 г.
// 
// Практически изпит
// 
// Име: Радослав Хубенов
// ФН: 45708
// Специалност: Информатика
// Курс: 3
// Административна група: 2
// Ден, в който се явявате на изпита: 31.01.22
// Начален час на изпита: 9:00
// Кой компилатор използвате: gcc

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

#include <forward_list>
#include <queue>
#include <vector>

using namespace std;

struct Tree {
    int val;
    vector<Tree*> children;

    ~Tree() {
        for(vector<Tree*>::iterator it = children.begin(); it != children.end(); ++it) {
            delete (*it);
        }
    }
};

string getNextWord(string::iterator& s) {
    string res = "";
    while((*s) != ' ') {
        res.push_back((*s));
    }

    return res;
}

vector<int> getNextBrotherhood(string::iterator& s, string::iterator& end) {
    vector<int> res;
    if(s == end) {
        return res;
    }
    while((*s) != '|') {
        s++;
    }
    s++;


    while((*s) != '|' && s != end) {
        if((*s) != ' ') {
            string num = getNextWord(s);
            res.push_back(stoi(num));
        } else {
            ++s;
        }
    }

    return res;
}

Tree* readTree(string fname) {
    // Function expects that the input and file structure is correct
    fstream f(fname);

    string line;
    Tree* curr = new Tree;

    // Read value for root tree
    getline(f, line);
    string::iterator s = line.begin();
    string::iterator end = line.end();
    vector<int> firstLevel = getNextBrotherhood(s, end);
    curr->val = firstLevel[0];

    vector<Tree*> level;
    vector<Tree*> nextLevel = level;
    level.push_back(curr);

    while(getline(f, line)) {
        string::iterator s = line.begin();
        string::iterator end = line.end();
        for(vector<Tree*>::iterator tree = level.begin(); tree != level.end(); ++tree) {
            vector<int> vals = getNextBrotherhood(s, end);
            for(vector<int>::iterator val = vals.begin(); val != vals.end(); ++val) {
                Tree* newTree = new Tree;
                newTree->val = (*val);
                (*tree)->children.push_back(newTree);
                nextLevel.push_back(newTree);
            }
        }
        level = nextLevel;
    }

    return curr;
}

int main()
{
	return 0;
}
