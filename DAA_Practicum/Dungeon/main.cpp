#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector< vector < pair<int, int> > > wg;
vector<char> gc;

int bestPathLevel = 9999999;

pair<int, int> getAdjNode(int s, int t) {
    for(int i = 0; i < wg[s].size(); ++i) {
        if(wg[s][i].first == t) 
            return wg[s][i];
    }
    return make_pair(0, 0);
}

void updateBestLevel(vector<int>& path) {
    int start = path[path.size() - 1];
    int maxLevel = getAdjNode(start, path[path.size() - 2]).second;
    for(int i = path.size() - 1; ; --i) {
        int currNode = path[i];
        pair<int, int> nextNode = getAdjNode(currNode, path[i-1]);

        int level = nextNode.second;

        if(level >= bestPathLevel)
            return;

        if(level > maxLevel)
           maxLevel = level;

        if(nextNode.first == start)
            break;
    }
    bestPathLevel = maxLevel;
}

void DFS(int currNode, int previousNode, vector<int> path, vector<char> colors) {

    colors[currNode] = 'g';

    path.push_back(currNode);

    for(int i = 0; i < wg[currNode].size(); ++i) {
       pair<int, int> node = wg[currNode][i];
       if(node.first == previousNode)
           continue;
       if(node.second >= bestPathLevel)
           continue;
       
       if(colors[node.first] == 'g' || colors[node.first] == 'b') {
            vector<int> copy = path;
            path.push_back(node.first);
            updateBestLevel(path);
            path.pop_back();
       } 
       else {
           DFS(node.first, currNode, path, colors);
       }
    }

    colors[currNode] = 'b';
    gc[currNode] = 'b';    

}


int main() {
    
    int n, m;

    cin >> n >> m;

    for(int i = 0; i < n; ++i) {
        vector< pair<int, int> > node;
        wg.push_back(node);
    }

    for( int i = 0; i < m; ++i) {
        
        int from, to, level;
        
        cin >> from >> to >> level;

        wg[from].push_back(make_pair(to, level));
        wg[to].push_back(make_pair(from, level));
    }

    for(int i = 0; i < n; ++i) {
        gc.push_back('w');
    }

    for(int i = 0; i < n; ++i) {
        if(gc[i] == 'w') {
            vector<int> path;
            DFS(i, -1, path, gc);
        }
    }

    cout << bestPathLevel << '\n';

    return 0;
}


