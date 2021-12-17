#include <iostream>
#include <vector>

int verticesCount, edgesCount, worldRecord;

int globalMinGear = 99999999;

struct Node {
    int num, gear, time;
};

std::vector< std::vector<Node> > adjList;

void addEdge(int start, Node end) {
    adjList[start].push_back(end);
}


void weightedDFS(int start, int end, std::vector<int> path, std::vector<char> colors, int time, int minGear) {
    path.push_back(start);
    colors[start] = 'g';

    if(time > worldRecord)
        return;

    if(minGear > globalMinGear)
        return;

    if(start == end) {
        globalMinGear = minGear;
        return;
    }

    for(int i = 0; i < adjList[start].size(); ++i) {
        Node currNode = adjList[start][i];
        if(colors[adjList[start][i].num] == 'w') {
            time += currNode.time;
            if(minGear < currNode.gear)
                minGear = currNode.gear;
            weightedDFS(currNode.num, end, path, colors, time, minGear);
        }
    }

    colors[start] = 'b';
}

void generateValidPaths() {
    std::vector<int> path;
    std::vector<char> colors;

    for(int i = 0; i < verticesCount + 1; ++i)
        colors.push_back('w');

    weightedDFS(1, verticesCount, path, colors, 0, 0);
}

int main() {

    std::cin >> verticesCount >> edgesCount >> worldRecord;


    for(int i = 0; i < verticesCount + 1; ++i) {
        std::vector<Node> edges;
        adjList.push_back(edges);
    }

    for(int i = 0; i < edgesCount; ++i) {
        int startNode, endNode, gear, time; 

        std::cin >> startNode >> endNode >> gear >> time;

        Node end;
        end.num = endNode;
        end.gear = gear;
        end.time = time;

        addEdge(startNode, end);
    }

    generateValidPaths();

    if(globalMinGear == 99999999){
        std::cout << "-1" << "\n";
        return 0;
    }
   
    std::cout << globalMinGear << "\n";

    return 0;
}
