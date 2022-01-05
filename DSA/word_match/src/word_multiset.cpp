#include "../headers/interface.h"

using namespace std;

void WordsMultiset::add(const string& word, size_t times) {

}

bool WordsMultiset::contains(const string& word) const {
    return true;
}

size_t WordsMultiset::countOf(const string& word) const {
    return 1;
}

size_t WordsMultiset::countOfUniqueWords() const {
    return 1;
}

multiset<string> WordsMultiset::words() const {
    return multiset<string>();
}

