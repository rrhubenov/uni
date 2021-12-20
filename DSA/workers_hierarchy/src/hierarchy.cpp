#include "../headers/interface.h"

Hierarchy::Hierarchy(Hierarchy&& r) noexcept {


}


Hierarchy::Hierarchy(const Hierarchy& r) {


}

Hierarchy::Hierarchy(const string& data) {


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
    return true;
}

int Hierarchy::num_employees() const {
    return 1;
}

int Hierarchy::num_overloaded(int level) const {
    return 3;
}

string Hierarchy::manager(const string& name) const {
    return "";
}

int Hierarchy::num_subordinates(const string& name) const {
    return 3;
}

unsigned long Hierarchy::getSalary(const string& who) const {
    return 3;
}

bool Hierarchy::fire(const string& who) {
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



