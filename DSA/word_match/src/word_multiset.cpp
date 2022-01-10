#include "../headers/interface.h"

using namespace std;

void WordsMultiset::add(const string& word, size_t times) {
    hm.insert(word, times);
}

bool WordsMultiset::contains(const string& word) const {
    return hm.find(word);
}

size_t WordsMultiset::countOf(const string& word) const {
    return hm.find(word);
}

size_t WordsMultiset::countOfUniqueWords() const {
    return hm.getUniqueSize();
}

size_t WordsMultiset::countOfAllWords() const {
    return hm.getSize();
}

multiset<string> WordsMultiset::words() const {
    multiset<string> ms = multiset<string>();
    for(HashMap::iterator it = hm.begin(); it != hm.end(); ++it) {
        for(int i = 0; i < it->first; ++i) {
            ms.insert(it->second);
        }
    }
    return ms;
}

