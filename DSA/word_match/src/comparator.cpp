#include "../headers/interface.h"

using namespace std;

ComparisonReport Comparator::compare(istream& a, istream& b) {
    HashMap hm1, hm2;
    WordsMultiset common, unique1, unique2;

    string buffer;

    while(a >> buffer) {
        hm1.insert(buffer);
    }
    while(b >> buffer) {
        hm2.insert(buffer);
    }

    // Add common words and unique words for stream a
    for(HashMap::iterator it = hm1.begin(); it != hm1.end(); ++it) {
        size_t count = hm2.find(it->second);
        if(count) {
            size_t min = 0;
            if(count < it->first) {
                // Insert unique for unique1
                for(unsigned i = 0; i < (it->first - count); ++i) {
                    unique1.add(it->second);
                }
                min = count;
            } else {
                min = it->first;
            }
            for(unsigned i = 0; i < min; ++i) {
                common.add(it->second);
            }
        } else {
            for(unsigned i = 0; i < it->first; ++i) {
                unique1.add(it->second);
            }
        }
    }

    //Add unique words for stream b
    for(HashMap::iterator it = hm2.begin(); it != hm2.end(); ++it) {
        size_t count = hm1.find(it->second);
        if(count < it->first) {
            for(int i = 0; i < (it->first - count); ++i) {
                unique2.add(it->second);
            }
        }
    }

    return ComparisonReport {common, {unique1, unique2}};
}
