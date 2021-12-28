#include "../headers/interface.h"
#include <string>
#include <cassert>

using namespace std;

Hierarchy::Hierarchy(Hierarchy&& r) noexcept: tree(move(r.tree)) {}

Hierarchy::Hierarchy(const Hierarchy& r): tree(Tree<string>(r.tree)) {}


Hierarchy::Hierarchy(const string& data) {
    //TODO: There can be white spaces around the delim. See tests.cpp line 91
    //TODO: Clean up code duplication
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

            tree.insertNode(worker, boss);

            line = "";
        } else {
            line.push_back(*it);
        }
    }
    if(line != "") {
        string boss = line.substr(0, line.find(delimeter));
        string worker = line.substr(line.find(delimeter)+1, line.length());
        boss.erase(0, boss.find_first_not_of(' '));
        boss.erase(boss.find_last_not_of(' ') + 1);
        worker.erase(0, worker.find_first_not_of(' '));
        worker.erase(worker.find_last_not_of(' ') + 1);

        if(boss.find(' ') != string::npos || worker.find(' ') != string::npos) {
            throw exception();
        }

        tree.insertNode(worker, boss);
    }
}

Hierarchy::~Hierarchy() noexcept {


}

string Hierarchy::print() const {
    return tree.print();
}

int Hierarchy::longest_chain() const {
    if(tree.getSize() == 1) {
        return 0;
    }

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
    try {
        const Tree<string>& worker = tree.search(name);
        return worker.children_count();
    } catch(...) {
        return -1;
    }
}

unsigned long Hierarchy::getSalary(const string& who) const {
    try {
        Tree<string> worker = tree.search(who);
        unsigned direct_count = worker.children_count();
        unsigned remaining = worker.getSize() - direct_count - 1;

        return 500*direct_count + 50*remaining;
    } catch(...) {
        return -1;
    }
}

bool Hierarchy::fire(const string& who) {
    try {
        if(who == "Uspeshnia") {
            return false;
        }
        tree.remove(who);
        return true;
    } catch(runtime_error e) {
        if(strcmp(e.what(), "Element not found") == 0) {
            return false;
        } else {
            throw e;
        }
    }
}

bool Hierarchy::hire(const string& who, const string& boos) {
    //TODO: return false if can't hire
    try {
        tree.insertNode(who, boos);
        return true;
    } catch(runtime_error e) {
        if(strcmp(e.what(), "Element not found") == 0) {
            return false;
        } else {
            throw e;
        }
    }
}

void Hierarchy::incorporate()  {
    for(Tree<string>::riterator it1 = tree.rbegin(); it1 != tree.rend(); ++it1) {
        if(it1->children_count() >= 2) {

            forward_list<Tree<string>*>* children = it1->getChildren();
            Tree<string>* max = children->front();
            unsigned max_salary = 0;
            for(forward_list<Tree<string>*>::iterator it2 = children->begin(); it2 != children->end(); ++it2) {
                unsigned ccount = (*it2)->children_count();
                unsigned remaining = (*it2)->getSize() - ccount - 1;
                unsigned salary = 500*ccount + 5*remaining;
                if(salary > max_salary) {
                    max_salary = salary;
                    max = *it2;
                }
            }

            forward_list<Tree<string>*> toMove;
            for(forward_list<Tree<string>*>::iterator it2 = children->begin(); it2 != children->end(); ++it2) {
                if(*it2 != max) {
                    toMove.push_front(*it2);
                }
            }
            for(forward_list<Tree<string>*>::iterator it2 = toMove.begin(); it2 != toMove.end(); ++it2) {
                this->hire((*it2)->getData(), max->getData());
            }

        }
    }
}

void Hierarchy::modernize() {
    for(Tree<string>::riterator it = tree.rbegin(); it != tree.rend(); ++it) {
        if(it->getHeight() % 2 == 0 && it->children_count() > 0) {
            this->fire(it->getData());
        }
    }
}

Hierarchy Hierarchy::join(const Hierarchy& right) const {
    // Копираме лявото дърво
    // Итерираме през дясното дърво
    //  За всеки работник от дясното:
    //      Ако се намира в лявото дърво също:
    //          добавяме всички деца на работника в дясното дърво в лявото
    //          Ако имат различни шефове && ако левия е по-ниско в йерархията:
    //              insertNode(работника, десния шеф)
    //      Ако не се намира в лявото дърво:
    //          итерираме през цялото поддърво на работника и вкарваме него и всичките му деца
    Hierarchy result = Hierarchy(*this);
    Tree<string>::const_iterator it = right.tree.cbegin();
    ++it;
    for(;it != right.tree.cend(); ++it) {
        if(result.find(it->getData())) {
            forward_list<Tree<string>*>* children = it->getChildren();
            if(children != nullptr) {
                for(forward_list<Tree<string>*>::const_iterator child = children->cbegin(); child != children->cend(); ++child) {
                    result.hire((*child)->getData(), it->getData());
                }
            }
            const Tree<string>& left_parent = result.tree.search(it->getData());
            const Tree<string>* right_parent = it->getParent();
            assert(right_parent != nullptr);
            if(left_parent.getData() != right_parent->getData() && left_parent.getHeight() > right_parent->getHeight()){
                result.tree.insertNode(it->getData(), right_parent->getData());
            } else if(left_parent.getData() != right_parent->getData() && left_parent.getHeight() == right_parent->getHeight()) {
                if(left_parent.getData() > right_parent->getData()) {
                    result.tree.insertNode(it->getData(), right_parent->getData());
                }
            }
        } else {
            for(Tree<string>::const_iterator subtree = it->cbegin(); subtree != it->cend(); ++subtree) {
                result.hire(it->getData(), it->getParent()->getData());
            }
        }
    }
    return result;
}



