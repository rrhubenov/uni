#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class CharStack {
private:
    char* data;
    int size;
    int capacity;
public:
    CharStack() {
        size = 0;
        data = new char[10];
        capacity = 10;
    }

    ~CharStack() {
        delete[] data;
    }

    void push(char a) {
        if(size == (capacity - 1)) {
            char* old = data;
            data = new char[size * 2];
            for(size_t i = 0; i < size; ++i) {
                data[i] = old[i];
            }

            delete[] old;
        }
        data[size] = a;
        size++;
    }

    void pop() {
        if(size == 0) {
            throw runtime_error("Pop empty");
        }

        size--;
    }

    char top() {
        if(size == 0) {
            throw runtime_error("Top empty");
        }
        return data[size-1];
    }

    bool isEmpty() {
        return size == 0;
    }
};

bool elem(char a, string b) {
    if(b == "") {
        return false;
    }
    if(a == b.front()) {
        return true;
    } else {
        return elem(a, b.substr(1, string::npos));
    }
}

bool match(char lb, char rb) {
    switch(lb) {
    case '(':
        if(rb != ')')
            return false;
    case '[':
        if(rb != ']')
            return false;
    case '{':
        if(rb != '}')
            return false;
    default:
        return true;
    }
}

string check(CharStack& s, string bs) {
    if(bs == "") {
        return s.isEmpty() ? "YES" : "NO";
    }

    if(elem(bs.front(), "([{")) {
        s.push(bs.front());
    } else {
        if(!match(bs.front(), s.top())) {
            return "NO";
        } else {
            s.pop();
        }
    }

    return check(s, bs.substr(1, string::npos));
}

int main() {
    string bs;

    cin >> bs;

    for(string::const_iterator it = bs.cbegin(); it != bs.cend(); ++it) {
        if(! elem(*it, "{}[]()")) {
            cerr << "Please enter only brackets\n";
            exit(1);
        }
    }

    CharStack s;

    cout << check(s, bs) << endl;

    return 0;
}
