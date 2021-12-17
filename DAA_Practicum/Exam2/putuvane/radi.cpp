#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <tuple>
 
using std::priority_queue; 
using std::vector; 
using std::map; 
using std::list; 
using std::cin; 
using std::cout; 
using std::endl; 
 
vector< list<int> > graph; 
map< std::pair<int, int>, int > cost; 
 
void findAllPathsLen(int u, int d, bool visited[], int path[], int& path_index, vector< list<int> > graph, map< std::pair<int, int>, int >, priority_queue< int, vector<int>, std::greater<int> >& allRoads)
{
    visited[u] = true;
    path[path_index] = u;
    path_index++;
 
    if (u == d) 
    {
        int allKm = 0; 
        for (int i = 0; i < path_index - 1; i++)
        {
            allKm += cost[std::make_pair(path[i], path[i + 1])];
        }
        allRoads.push(allKm);
    }
    else 
    {
        list<int>::iterator i;
        for (i = graph[u].begin(); i != graph[u].end(); ++i)
            if (!visited[*i])
                findAllPathsLen(*i, d, visited, path, path_index, graph, cost, allRoads);
    }
 
    path_index--;
    visited[u] = false;
}
 
int findCount(int s, int d, vector< list<int> > graph, map< std::pair<int, int>, int> cost, int n)
{
    bool* visited = new bool[n];
 
    int* path = new int[n];
 
    int path_index = 0; 
 
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
 
    priority_queue< int, vector<int>, std::greater<int> > allRoads;
 
    findAllPathsLen(s, d, visited, path, path_index, graph, cost, allRoads);
 
    int count = 0; 
    int minRoad = 0;
 
    if (!allRoads.empty())
    {
        minRoad = allRoads.top();
        count++; 
        allRoads.pop();
        while (minRoad == allRoads.top() && !allRoads.empty())
        {
            count++;
            allRoads.pop();
        }
    }
 
    return count; 
}
 
int main()
{
	int n, m; 
	cin >> n >> m; 
	int from, to, km; 
 
    graph.resize(n); 
 
	for (int i = 0; i < m; i++)
	{
		cin >> from >> to >> km; 
		graph[from].push_back(to); 
        graph[to].push_back(from);
		cost[std::make_pair(from, to)] = km; 
        cost[std::make_pair(to, from)] = km; 
	}
 
    int q; 
    cin >> q; 
    vector<int> output; 
    output.resize(q); 
 
    for (int i = 0; i < q; i++)
    {
        cin >> from >> to; 
        output[i] = findCount(from, to, graph, cost, n);
    }
 
    for (int i = 0; i < q; i++)
    {
        cout << output[i] << " "; 
    }
 
	return 0; 
}


