#include <iostream>


int n, m;

int qs[1000000];

int main() {

    MinCostArborescence arborescence;

    cin >> n;

    for(int i = 0; i < n; ++i) {
        cin >> qs[i];
    }

    cin >> m;

    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if(qs[a] > qs[b]) {
            Edge e;
            e.u = a;
            e.v = b;
            e.dist = c;
            arborescence.add_Edge(e);
        }
    }

    cout << arborescence.dir_mst(1);

    return 0;
}
