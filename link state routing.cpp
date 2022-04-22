#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5, inf = 1e9;

typedef pair<int, int> pii;

int n, m, dist[N][N];
vector<pii> gr[N];

void dijkstra(int src) {
    dist[src][src] = 0;
    set<pii> st;
    st.emplace(0, src);

    while(!st.empty()) {
        auto u = st.begin()->second;
        st.erase(st.begin());
        for(auto &[v, w]: gr[u]) {
            if(dist[v][src] > dist[u][src] + w) {
                auto it = st.find({dist[v][src], v});
                if(it != st.end()) st.erase(it);
                dist[v][src] = dist[u][src] + w, st.emplace(dist[v][src], v);
            }
        }
    }

    cout<<"Routing table for "<<src<<"\n";
    for(int x=1;x<=n;x++) {
        for(int y=1;y<=n;y++) cout<<dist[x][y]<<" ";
        cout<<'\n';
    }
    cout<<'\n';
}

int main() {

    cout<<"Enter number of nodes:\n";
    cin>>n;
    cout<<"Enter number of links:\n";
    cin>>m;

    for(int x=0;x<m;x++) {
        cout<<"Enter the vertices having a link and the cost of the link (separated by space):\n";
        int u, v, w;
        cin>>u>>v>>w;
        gr[u].emplace_back(v, w), gr[v].emplace_back(u, w);
    }

    for(int x=1;x<=n;x++) fill(dist[x] + 1, dist[x] + n + 1, inf);
    for(int x=1;x<=n;x++) dijkstra(x);

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
