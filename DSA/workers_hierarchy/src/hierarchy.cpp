#include "../headers/interface.h"
#include <string>

using namespace std;

Hierarchy::Hierarchy(Hierarchy&& r) noexcept {


}


Hierarchy::Hierarchy(const Hierarchy& r) {


}

Hierarchy::Hierarchy(const string& data) {
    //TODO
}

Hierarchy::~Hierarchy() noexcept {


}

string Hierarchy::print() const {
    return "";
}

int Hierarchy::longest_chain() const {
    return 3;
}

bool Hierarchy::find(const string& name) const {
    try{
        tree.search(name);
        return true;
    } catch(...) {
        return false;
    }
}

int Hierarchy::num_employees() const {
    return tree.getSize();
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
            return it->getParent()->getData();
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
    return true;
}

void Hierarchy::incorporate()  {

}

void Hierarchy::modernize() {

}

Hierarchy Hierarchy::join(const Hierarchy& right) const {
    return Hierarchy("");
}



