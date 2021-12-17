#include<iostream>

using std::cin; 
using std::cout; 
using std::endl; 

int xm, ym, h;

// STARTING POINT IS (1,0,1)
// ENDING POINT IS   (xm-1,ym,1)

long long yDPTable[80][21];
long long zDPTable[22][22];

long long mod = 1000000007;

long long countYPaths(int point, int numOfSteps) {
    //Use a padding of 15 to account for negative points
    if(yDPTable[point + 25][numOfSteps] >= 0)
        return yDPTable[point + 25][numOfSteps];

    int s = numOfSteps - 1;

    yDPTable[point + 25][numOfSteps] = countYPaths(point - 1, s) + countYPaths(point + 1, s) + countYPaths(point, s);

    return yDPTable[point + 25][numOfSteps];
}

long long countZPaths(int point, int numOfSteps) {

    if(point == 0) return 0;
    if(point > h) return 0;
    if(zDPTable[point][numOfSteps] >= 0)
        return zDPTable[point][numOfSteps];

    int s = numOfSteps - 1;

    zDPTable[point][numOfSteps] = countZPaths(point-1, s) + countZPaths(point+1, s) + countZPaths(point, s);

    return zDPTable[point][numOfSteps];
}

long long initZDPTable(int point, int numOfSteps) {
    for(int i = 0; i < 22; ++i) {
        for(int j = 0; j < 22; ++j) {
            if(j == 0) {
                zDPTable[i][j] = 0;
            } else{
                zDPTable[i][j] = -1;
            }
        }
    }

    zDPTable[1][0] = 1;

    return countZPaths(point, numOfSteps);
}

long long initYDPTable(int point, int numOfSteps) {
    for(int i = 0; i < 80; ++i) {
        for(int j = 0; j < 21; ++j) {
            if(j == 0) {
                yDPTable[i][j] = 0;
            } else {
                yDPTable[i][j] = -1;
            }
        }
    }

    yDPTable[25][0] = 1;

    return countYPaths(point, numOfSteps);
}

int main()
{
    cin >> xm >> ym >> h; 

    long long yPaths = initYDPTable(ym, xm-2);
    long long zPaths = initZDPTable(1, xm-2);

    cout << (yPaths*zPaths) % mod << endl;

	return 0; 
}

