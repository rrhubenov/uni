#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int n, m, q;

vector< vector < pair<int, int> > > adjList;

int currShortest = 99999999;
int counter = 0;

vector< pair<int, int> > targets;

typedef pair<int, int> pi;

int findPaths(int startNode, int endNode) {
    int distances[555];
    int paths[555];

    for(int i = 0; i < 555; ++i) {
        distances[i] = 99999999;
        paths[i] = 0;
    }

    priority_queue<pi, vector<pi>, greater<pi> > queue;

    queue.push(make_pair(0, startNode));

    distances[startNode] = 0;
    paths[startNode] = 1;

    while(!queue.empty()) {
        int currNode = queue.top().second;
        int length = queue.top().first;

        queue.pop();

        for(unsigned i = 0; i < adjList[currNode].size(); ++i) {
            int child = adjList[currNode][i].first;
            int weight = adjList[currNode][i].second;

            if(distances[child] > distances[currNode] + weight) {
                queue.push(make_pair(length+ weight, child));
                distances[child] = distances[currNode] + weight;
                paths[child] = paths[currNode];
            }
            else if(distances[child] == distances[currNode] + weight) {

                paths[child] = paths[child] + paths[currNode];
            }
        }
    }
    
    return paths[endNode];
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

        cout << findPaths(targets[i].first, targets[i].second) << " ";
    }

    return 0;
}
