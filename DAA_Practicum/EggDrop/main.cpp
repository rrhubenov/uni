#include<iostream>

using namespace std;


int numOfEggs, numOfFloors;


int solve(int numOfEggs, int numOfFloors) {
    if(numOfEggs == 1) {
        return numOfFloors - 1;
    } else if(numOfFloors == 1) {
        return 0;
    } else {
        return 1 + solve(numOfEggs - 1, numOfFloors / 2);
    }

}

int main() {

    cin >> numOfEggs >> numOfFloors; 

    cout << solve(numOfEggs, numOfFloors);
    
    return 0;
}
