#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL INF = (1LL<<60);
vector<vector<pair<int, int>>> graph;

//SSSP
//doesn't work if the graph has negative cycles (thats np hard)
//works in O(VE)
//Can detect negative cycles. To detect do the relaxation one more time.
vector<LL> Bellman_Ford(int n, int s, vector<tuple<int, int, LL>> &edges){
    vector<LL> dist(n+1, INF);
    dist[s] = 0;

    for(int i = 1; i<=n-1; i++){
        for(auto [u, v, w]: edges){
            if(dist[u] != INF) dist[v] = min(dist[v], dist[u] + w);
        }
    }

    return dist;
}

//SSSP
//doesn't work if the graph has negatice weight
//works in O((V + E)logn)
//tested at CSES (0.12 sec for n= 1e5, m = 2e5)
vector<LL> Dijkstra(int n, int s){
    vector<LL> dist(n+1, INF);
    vector<bool> vis(n+1, 0);

    priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>>> pq;
    dist[s] = 0; pq.push({dist[s], s});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(vis[u]) continue;
        vis[u] = true;

        for(auto [v, w]: graph[u]){
            if(dist[v] > w + dist[u]){
                dist[v] = w + dist[u];
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

//ASSP
//doesn't work if the graph has negative cycles (thats np hard)
//Works in O(V^3)
void Floyd_Warshal(int n, vector<vector<LL>> &dist){
    for(int k = 1; k<=n; k++){
        for(int u = 1; u<=n; u++){
            for(int v = 1; v<=n; v++){
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
            }
        }
    }
}

//ASSP
//works in O((VE + V^2)logV)
vector<vector<LL>> Johnson(int n, vector<tuple<int, int, LL>> &edges){
    for(int i = 1; i<=n; i++) edges.emplace_back(n+1, i, 0);
    vector<LL> delta = Bellman_Ford(n+1, n+1, edges);
    for(int i = 1; i<=n; i++) edges.pop_back();

    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            graph[i][j].second+= delta[i] - delta[graph[i][j].first];
        }
    }

    vector<vector<LL>> dist(n+1);
    for(int i = 1; i<=n; i++){
        dist[i] = Dijkstra(n, i);
        for(int j =1; j<=n; j++){
            dist[i][j]-= delta[i] - delta[j];
        }
    }

    return dist;
}