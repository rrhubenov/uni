#include <iostream>
#include <stdlib.h>
#include <algorithm>

long long arr[100000];
int n;

using namespace std;

long long solve() {
    
    long long sum = 0;

    for(int i = 0; i < n; ++i) {
        if(arr[i] > 0) {
            sum += arr[i];
        }
    }

    
    if(sum % 2 == 0) {
        return sum;
    } 

    long long currMax = -999999999999999;

    for(int i = 0 ; i < n; ++i) {
        if(arr[i] % 2 != 0) {
            if(arr[i] > 0) {
                currMax = max(currMax, sum - arr[i]);
            } else {
                currMax = max(currMax, sum + arr[i]);
            }
                
        }
    }

    return currMax;
}

int main() {
    cin >> n;

    for(int i = 0 ; i< n; ++i) {
        cin >> arr[i];
    }

    cout << solve() << '\n';

    return 0;
}
