#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector< vector < pair<int, int> > > wg;
int level = -1;
int n, m;

vector<char> colors;

struct Edge {
    int from;
    int to;
    int level;

    Edge(int from, int to, int level) {
        this->from = from;
        this->to = to;
        this->level = level;
    }
};

vector<Edge> edges;

bool cmpEdge(Edge a, Edge b) {
    return a.level > b.level;
}

void DFS(int currNode, int previousNode, vector<char> colors) {

    colors[currNode] = 'g';

    for(int i = 0; i < wg[currNode].size(); ++i) {
       pair<int, int> node = wg[currNode][i];
       if(node.first == previousNode)
           continue;

       if(colors[node.first] == 'g' || colors[node.first] == 'b') {
           level = 100;
       }
       else {
           DFS(node.first, currNode, colors);
       }
    }

    colors[currNode] = 'b';
}

void DFSWholeGraph() {
    vector<char> colors;

    for(int i = 0; i < n; ++i) {
        colors.push_back('w');
    }

    for(int i = 0; i < n; ++i) {
        if(colors[i] == 'w' && level == -1) {
            DFS(i, -1, colors);
        }
    }
}

int main() {
    

    cin >> n >> m;

    for( int i = 0; i < m; ++i) {
        
        int from, to, level;
        
        cin >> from >> to >> level;

        edges.push_back(Edge(from, to, level));
    }

    sort(edges.begin(), edges.end(), cmpEdge);

    for(int i = 0; i < n; ++i) {
        vector< pair<int, int> > node;
        wg.push_back(node);
    }
   
    for(int i = 0; i < 2; ++i) {
        Edge edge = edges[edges.size() - 1];
        wg[edge.from].push_back(make_pair(edge.to, edge.level));
        edges.pop_back();
    }

    for(int i = 0; i < 4; ++i) {
        Edge edge = edges[edges.size() - 1];
        wg[edge.from].push_back(make_pair(edge.to, edge.level));
        edges.pop_back();
        DFSWholeGraph();
        cout << edges.size() << '\n';
        for(int j = 0; i < edges.size(); ++i) {
            cout << edges[i].level << '\n';
        }
    }

    return 0;
}


