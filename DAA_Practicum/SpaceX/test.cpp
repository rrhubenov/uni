#include<iostream>

using std::cin; 
using std::cout; 
using std::endl; 

int xm, ym, h;

// STARTING POINT IS (1,0,1)
// ENDING POINT IS   (xm-1,ym,1)

int yM[40][21];
int zM[21][21];

int countYPaths(int point, int numOfSteps) {
    if(numOfSteps == 0 && point == 0) {
        return 1;
    } else if (numOfSteps == 0 && point != 0) {
        return 0;
    }

    int s = numOfSteps - 1;

    int downPaths, upPaths, staticPaths;

    if(yM[point - 1 + 15][s] != -1) {
        downPaths = yM[point - 1 + 15][s];
    } else {
        downPaths = countYPaths(point - 1, s);
        yM[point - 1 + 15][s] = downPaths;
    }
    if(yM[point + 1 + 15][s] != -1) {
        upPaths = yM[point + 1 + 15][s];
    } else {
        upPaths = countYPaths(point + 1, s);
        yM[point + 1 + 15][s] = upPaths;
    }
    if(yM[point + 15][s] != -1) {
        staticPaths = yM[point + 15][s];
    } else {
        staticPaths = countYPaths(point, s);
        yM[point + 15][s] = staticPaths;
    }

    return upPaths + downPaths + staticPaths;
}

int countZPaths(int point, int numOfSteps) {

    if(numOfSteps == 0 && point == 1) {
        return 1;
    } else if(numOfSteps == 0 && point != 1) {
        return 0;
    }

    int s = numOfSteps - 1;

    int upPaths;
    int downPaths;
    int staticPaths;

    if(point > 1 && point < h) {

        if(zM[point - 1][s] != -1) {
            downPaths = zM[point - 1][s];
        } else {
            downPaths = countZPaths(point - 1, s);
            zM[point - 1][s] = downPaths;
        }
        if(zM[point + 1][s] != -1) {
            upPaths = zM[point + 1][s];
        } else {
            upPaths = countZPaths(point + 1, s);
            zM[point + 1][s] = upPaths;
        }
        if(zM[point][s] != -1) {
            staticPaths = zM[point][s];
        } else {
            staticPaths = countZPaths(point, s);
            zM[point][s] = staticPaths;
        }

        return downPaths + upPaths + staticPaths;
    } else if(point > 1) {

        if(zM[point - 1][s] != -1) {
            downPaths = zM[point - 1][s];
        } else {
            downPaths = countZPaths(point - 1, s);
            zM[point - 1][s] = downPaths;
        }
        if(zM[point][s] != -1) {
            staticPaths = zM[point][s];
        } else {
            staticPaths = countZPaths(point, s);
            zM[point][s] = staticPaths;
        }

        return downPaths + staticPaths;
    } else if(point < h) {

        if(zM[point + 1][s] != -1) {
            upPaths = zM[point + 1][s];
        } else {
            upPaths = countZPaths(point + 1, s);
            zM[point + 1][s] = upPaths;
        }
        if(zM[point][s] != -1) {
            staticPaths = zM[point][s];
        } else {
            staticPaths = countZPaths(point, s);
            zM[point][s] = staticPaths;
        }

        return upPaths + staticPaths; 
    } else {

        if(zM[point][s] != -1) {
            staticPaths = zM[point][s];
        } else {
            staticPaths = countZPaths(point, s);
            zM[point][s] = staticPaths;
        }

        return staticPaths;
    }
}

int main()
{
    cin >> xm >> ym >> h; 

    for(int i = 0; i < 21; ++i) {
        for(int j = 0; j < 21; ++j) {
            zM[i][j] = -1;
        }
    }

    for(int i = 0; i < 40; ++i) {
        for(int j = 0; j < 21; ++j) {
            yM[i][j] = -1;
        }
    }
    cout << countYPaths(ym, xm-2) * countZPaths(1, xm-2);

	return 0; 
}
