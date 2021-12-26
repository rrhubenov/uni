#include "../headers/interface.h"
#include <string>

using namespace std;

Hierarchy::Hierarchy(Hierarchy&& r) noexcept {


}


Hierarchy::Hierarchy(const Hierarchy& r) {


}

Hierarchy::Hierarchy(const string& data) {
    //TODO: There can be white spaces around the delim. See tests.cpp line 91
    string line;
    string delimeter = "-";

    for(string::const_iterator it = data.cbegin(); it != data.cend(); ++it) {
        if(*it == '\n') {
            if(line.find('-') == string::npos) {
                throw exception();
            }

            string boss = line.substr(0, line.find(delimeter));
            string worker = line.substr(line.find(delimeter)+1, line.length());
            boss.erase(0, boss.find_first_not_of(' '));
            boss.erase(boss.find_last_not_of(' ') + 1);
            worker.erase(0, worker.find_first_not_of(' '));
            worker.erase(worker.find_last_not_of(' ') + 1);

            if(boss.find(' ') != string::npos || worker.find(' ') != string::npos) {
                throw exception();
            }

            try {
                tree.insertNode(worker, boss);
            } catch(...) {
                // TODO
            }

            line = "";
        } else {
            line.push_back(*it);
        }
    }
}

Hierarchy::~Hierarchy() noexcept {


}

string Hierarchy::print() const {
    return tree.print();
}

int Hierarchy::longest_chain() const {
    unsigned max = 0;

    for(Tree<string>::const_iterator it = tree.cbegin(); it != tree.cend(); ++it) {
        if(it->getHeight() > max) {
            max = it->getHeight();
        }
    }

    return max;
}

bool Hierarchy::find(const string& name) const {
    if(tree.getSize() == 1) {
        return false;
    } else {
        try{
            tree.search(name);
            return true;
        } catch(...) {
            return false;
        }
    }
}

int Hierarchy::num_employees() const {
    if(tree.getSize() == 1) {
        return 0;
    } else {
        return tree.getSize();
    }
}

int Hierarchy::num_overloaded(int level) const {
    unsigned count = 0;
    for(Tree<string>::const_iterator it = tree.cbegin(); it != tree.cend(); ++it) {
        if(it->getSize() > level) {
            count++;
        }
    }
    return count;
}

string Hierarchy::manager(const string& name) const {
    for(Tree<string>::const_iterator it = tree.cbegin(); it != tree.cend(); ++it) {
        if(it->getData() == name) {
            if(it->getParent() == nullptr) {
                return "";
            } else {
                return it->getParent()->getData();
            }
        }
    }
    // TODO: Should there be exception checking?
    return "NOT FOUND!";
}

int Hierarchy::num_subordinates(const string& name) const {
    const Tree<string>& worker = tree.search(name);
    return worker.children_count();
}

unsigned long Hierarchy::getSalary(const string& who) const {
    Tree<string> worker = tree.search(who);
    unsigned direct_count = worker.children_count();
    unsigned remaining = worker.getSize() - direct_count;

    return 500*direct_count + 50*remaining;
}

bool Hierarchy::fire(const string& who) {
    tree.remove(who);
    return true;
}

bool Hierarchy::hire(const string& who, const string& boos) {
    //TODO: return false is can't hire
    tree.insertNode(who, boos);
    return true;
}

void Hierarchy::incorporate()  {

}

void Hierarchy::modernize() {

}

Hierarchy Hierarchy::join(const Hierarchy& right) const {
    return Hierarchy("");
}



