#include <iostream>
#include <list>
#include <vector>

using namespace std;

int n, m, k;

vector<int> adjList[1000];

int ks[10000];

bool visited[10000];

int BFS(int startNode, int endNode) {

    char colors[1000];
    int dist[1000];
    
    for(int i = 0; i < n; ++i) {
        colors[i] = 'w'; 
    }

    colors[startNode] = 'g';
    dist[startNode] = 0;

    list<int> queue;
    queue.push_back(startNode);

    while(!queue.empty()) {
        int currNode = queue.front();
        queue.pop_front();

        for(int i = 0; i < adjList[currNode].size(); ++i) {

            int adjNode = adjList[currNode][i];

            if(adjNode == endNode) {
                return dist[currNode] + 1;
            }

            bool shouldAvoid = false;

            for(int i = 0; i < k; ++i) {
                if(adjNode == ks[i] && !visited[ks[i]]) {
                    shouldAvoid = true;
                    break;
                }
            }

            if(shouldAvoid)
                continue;

            if(colors[adjNode] == 'w') {


                colors[adjNode] = 'g';
                dist[adjNode] = dist[currNode] + 1;
                queue.push_back(adjNode);
            }
        }

        colors[currNode] = 'b';
    }

    return -1;
}


int main() {
    
    cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
    }

    cin >> k;

    for(int i = 0; i < k; ++i) {
        int attraction;
        cin >> attraction;
        ks[i] = attraction;
        visited[attraction] = false;
    }

    int pathSum = 0;

    for(int i = 0; i < k-1; ++i) {
        int dist = BFS(ks[i], ks[i+1]); 

        if(dist == -1) {
            cout << -1;
            return 0;
        }
        visited[ks[i]] = true;
        pathSum += dist;
    }

    cout << pathSum;

    return 0;
}
