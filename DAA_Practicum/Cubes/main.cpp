#include <iostream>
#include <algorithm>

using namespace std;

int DPTable[100][1000][1000];

int R, B;

long long maxFloorReached = -9999999;
long long timesReached = 0;

int recur(int floor, int R, int B) {

    if(DPTable[floor][R][B] != 0)
        return DPTable[floor][R][B] - 1;

    if(R < floor && B < floor) {
        return floor;
    }

    if(R >= floor && B >= floor) {
        DPTable[floor][R][B] = max(recur(floor +1, R - floor, B) + 1, recur(floor+1, R, B -floor) + 1);
    } else if( R >= floor) {
        DPTable[floor][R][B] = recur(floor +1, R - floor, B) + 1;
    } else {
        DPTable[floor][R][B] = recur(floor +1, R, B-floor) + 1;
    }

    if(maxFloorReached < (DPTable[floor][R][B] - 1)) {
        maxFloorReached = DPTable[floor][R][B] - 1;
        timesReached = 1;
    } else if(maxFloorReached == (DPTable[floor][R][B] - 1)) {
        timesReached++;
    }

    return DPTable[floor][R][B] - 1;
}

int main() {
        
    cin >> R >> B;

    recur(1, R, B);

    cout << timesReached << '\n';

    return 0;
}
