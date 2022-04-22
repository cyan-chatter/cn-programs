#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5, inf = 1e9;

int n, m, dist[N][N];
vector<tuple<int, int, int>> edg;

void bellmanford(int src) {
    dist[src][src] = 0;
    while(1) {
        bool done = true;
        for(auto &[u, v, w]: edg) {
            if(dist[u][src] > dist[v][src] + w) {
                dist[u][src] = dist[v][src] + w;
                done = false;
            }
        }

        if(done) break;
    }

    cout<<"Routing table for "<<src<<"\n";
    for(int x=1;x<=n;x++) {
        for(int y=1;y<=n;y++) cout<<dist[x][y]<<" ";
        cout<<'\n';
    }
    cout<<'\n';
}

int main() {

//    cout<<"Enter number of nodes:\n";
    cin>>n;
//    cout<<"Enter number of links:\n";
    cin>>m;

    for(int x=0;x<m;x++) {
//        cout<<"Enter the vertices having a link and the cost of the link (separated by space):\n";
        int u, v, w;
        cin>>u>>v>>w;
        edg.emplace_back(u, v, w), edg.emplace_back(v, u, w);
    }

    for(int x=1;x<=n;x++) fill(dist[x] + 1, dist[x] + n + 1, inf);
    for(int x=1;x<=n;x++) bellmanford(x);

    for(int x=1;x<=n;x++) {
        for(int y=1;y<=n;y++) {
            cout<<"Minimum cost to reach node "<<x<<" is "<<dist[x][y]<<" from node "<<y<<"\n";
        }
    }

    return 0;
}
//5 6
//1 2 7
//1 5 1
//2 3 1
//3 4 2
//4 5 2
//5 2 8
