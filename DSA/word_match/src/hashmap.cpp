#include "../headers/hashmap.h"
#include <assert.h>
#include <string>
#include <utility>
#include <iostream>
using namespace std;


HashMap::iterator HashMap::begin() const {
    return iterator(&data[0], uniqueSize);
}

HashMap::iterator HashMap::end() const {
    return iterator(nullptr, uniqueSize);
}

HashMap::HashMap() {
    uniqueSize = 0;
    size = 0;
    capacity = 8;
    data = new forward_list<pair<unsigned, string>>[capacity];
}

HashMap::HashMap(const HashMap& other) {
    size = other.size;
    uniqueSize =other.uniqueSize;
    capacity = other.capacity;
    data = new forward_list<pair<unsigned, string>>[capacity];

    for(int i = 0; i < capacity; ++i) {
        data[i] = other.data[i];
    }
}

HashMap::~HashMap() {
    delete[] data;
}

float HashMap::load() const {
    return (float) uniqueSize/ (float) capacity;
}

unsigned HashMap::hash(const string word) const {
    unsigned hashV = 0;
    unsigned index = 0;
    // SALT^0*char1 + SALT^1*char2 + ... + SALT^(n-1)*charn
    for(string::const_reverse_iterator it = word.rbegin(); it != word.rend(); ++it) {
        hashV = SALT*hashV + *it;
        index++;
    }

    return hashV % capacity;
}

void HashMap::insert(const string word, const size_t times) {
    unsigned hashV = hash(word);
    size += times;
    forward_list<pair<unsigned, string>>::iterator it = data[hashV].begin();
    for(;it != data[hashV].end(); ++it) {
        if(it->second == word) {
            it->first += times;
            return;
        }
    }

    data[hashV].push_front(make_pair(times, word));
    uniqueSize++;

    if(load() > 0.7) {
        resize(capacity * 2);
    }
}

unsigned HashMap::find(const string word) const {
    unsigned hashV = hash(word);

    for(forward_list<pair<unsigned, string>>::const_iterator it = data[hashV].cbegin(); it != data[hashV].cend(); ++it) {
        if(it->second == word) {
            return it->first;
        }
    }

    return 0;
}

void HashMap::remove(const string word) {
    unsigned hashV = hash(word);
    forward_list<pair<unsigned, string>>::iterator it = data[hashV].begin();

    for(;it != data[hashV].end(); ++it) {
        if(it->second == word) {
            it->first--;
            break;
        }
    }

    if(it->first == 0) {
        data[hashV].remove(*it);
    }
}

void HashMap::resize(const unsigned newCapacity) {
    forward_list<pair<unsigned, string>>* newData = new forward_list<pair<unsigned, string>>[newCapacity];
    capacity = newCapacity;
    
    for(HashMap::iterator it = begin(); it != end(); ++it) {
        unsigned hashV = hash(it->second);
        newData[hashV].push_front(*it);
    }

    delete[] data;
    data = newData;
}


size_t HashMap::getSize() const {
    return size;
}

size_t HashMap::getUniqueSize() const {
    return uniqueSize;
}
