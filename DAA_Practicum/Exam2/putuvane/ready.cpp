
#include <iostream>
#include <vector>



using namespace std;

int n, m, q;

vector< vector < pair<int, int> > > adjList;

int currShortest = 99999999;
int counter = 0;

vector< pair<int, int> > targets;

void weightedDFS(int currNode, int end, std::vector<int> path, std::vector<char> colors, int currPathWeight) {
    path.push_back(currNode);
    colors[currNode] = 'g';

    if(currPathWeight > currShortest)
        return;

    if(currNode == end) {
        if(currPathWeight < currShortest) {
            counter = 1;
            currShortest = currPathWeight;
        } else if(currPathWeight == currShortest) {
            counter += 1;
        }

        return;
    }

    for(unsigned i = 0; i < adjList[currNode].size(); ++i) {
        pair<int, int> adjNode = adjList[currNode][i];
        if(colors[adjNode.first] == 'w') {
            weightedDFS(adjNode.first, end, path, colors, currPathWeight + adjNode.second);
        }
    }

    colors[currNode] = 'b';
}

int main() {

    cin >> n >> m; 

    adjList.resize(n + 1);

    for(int i = 0 ; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adjList[from].push_back(make_pair(to, weight));
        adjList[to].push_back(make_pair(from, weight));
    }

    cin >> q;

    for(int i =0; i < q; ++i) {
        int from, to;
        cin >> from >> to;

        targets.push_back(make_pair(from, to));

        targets[i] = make_pair(from, to);
    }

    for(int i = 0; i < q; ++i) {
        std::vector<int> path;
        std::vector<char> colors;

        for(int i = 0; i < n + 1; ++i)
            colors.push_back('w');

        weightedDFS(targets[i].first, targets[i].second, path, colors, 0);

        cout << counter << " ";

        counter = 0;
        currShortest = 99999999;
    }

    return 0;
}
