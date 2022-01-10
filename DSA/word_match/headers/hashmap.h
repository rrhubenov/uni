#include <vector>
#include <forward_list>
#include <string>
#include <utility>

using namespace std;

class HashMap {
private:
    const unsigned SALT = 211;

    unsigned size, capacity;
    forward_list<pair<unsigned, string>>* data;

    float load() const;
    void resize(const unsigned newSize);

public:

    unsigned hash(const string word) const;
    class iterator;

    iterator begin();
    iterator end() const;

    HashMap();
    ~HashMap();

    void insert(const string word);
    unsigned find(const string word) const;
    void remove(const string word);
};

class HashMap::iterator {
    private:
        friend iterator HashMap::begin();
        friend iterator HashMap::end() const;

        unsigned size, count;
        forward_list<pair<unsigned, string>>* bucketPtr;
        forward_list<pair<unsigned, string>>::iterator it; 
    public:
        iterator(forward_list<pair<unsigned, string>>* ptr, const unsigned size): size(size), count(0), bucketPtr(ptr) {
            // assert(size != 0);
            if(bucketPtr != nullptr) {
                it = bucketPtr->begin();
                while(it == bucketPtr->end()) {
                    bucketPtr++;
                    it = bucketPtr->begin();
                }
            }
        }

        pair<unsigned, string>& operator*() { return *(it); }
        pair<unsigned, string>* operator->() { return &(*(it)); }

        iterator& operator++() {
            count++;
            if(count == size) {
                bucketPtr = nullptr;
                count = 0;
            } else {
                ++it;
                while(it == bucketPtr->end()) {
                    bucketPtr++;
                    it = bucketPtr->begin();
                }
            }
            return *this;
        }

        iterator operator++(int) {
            iterator res = *this;
            ++*this;
            return res;
        }

        bool operator==(const iterator& other) {
            return bucketPtr == other.bucketPtr &&
            count == other.count;
        }

        bool operator!=(const iterator& other) {
            return !(*this == other);
        }
};
