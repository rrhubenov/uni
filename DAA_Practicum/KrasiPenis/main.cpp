#include <iostream>

#define INT_MIN -99999999

using namespace std;

int n, k;
int arr[100000];

int solve(int start, int end) {
    int opt[100000];

    opt[0] = arr[start];
   
    for(int i = 1; i < end-start+1; ++i) {
        if((opt[i-1] + arr[start+i]) > arr[start+i]) {
            opt[i] = opt[i-1] + arr[i+start];
        } else{
            opt[i] = arr[i+start];
        }
    }

    int max = INT_MIN;
    for(int i = 0; i < end-start+1; ++i) {
        if(opt[i] > max) {
            max = opt[i];
        }
    }
    
    return max;
}

int extractSection(int start) {

    int numOfZeroes = 0;

    for(int i = start; i < n; ++i) {
        if(arr[i] == 0 && numOfZeroes == k) {
            return i;
        } else if(arr[i] == 0) {
            numOfZeroes++;
        }
    }

    return n-1;
}

int main() {
    
    cin >> n >> k;

    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int maxFound = INT_MIN;

    for(int i = 0; i < n - 1; ++i) {
        if(i == 0 || arr[i] == 0) {
            int sectionEnd = extractSection(i+1);

            int sectionMax = solve(i, sectionEnd);

            if(sectionMax > maxFound) {
                maxFound = sectionMax;
            }
        }
    }

    cout << maxFound << '\n';

    return 0;
}
