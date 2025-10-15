#include <bits/stdc++.h>
#include <DSU.h>
using namespace std;
typedef long long LL;

const LL INF = (1LL<<60);
vector<vector<pair<int, LL>>> graph; 

// uses DSU to find the spanning tree
// returns -INF if has multiple components
// works in 0.10sec for n = 1e5, m = 2e5
LL KruskalMST(int n, vector<tuple<int, int, LL>> &edges){
    sort(edges.begin(), edges.end(), 
        [](tuple<int, int, LL> &a, tuple<int, int, LL> &b){
            return get<2> (a) < get<2> (b);
        });

    DSU dsu(n);

    LL cost = 0, cnt = 0;
    for(auto [u, v, w]: edges){
        if(dsu.find_set(u) == dsu.find_set(v)) continue;
        dsu.union_sets(u, v);
        cnt++;
        cost+= w;
    }
    if(cnt < n-1) return -INF;
    return cost;
}


// return the cost of minimum spanning tree in O(ElogV)
// returns -INF if has multiple components
// works in 0.18sec for n = 1e5, m = 2e5
LL PrimsMST(int n){
    priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<pair<LL, int>>> pq;
    vector<bool> vis(n+1, 0);
    vector<int> p(n+1, 0); // the spanning tree
    vector<LL> key(n+1, INF);

    key[1] = 0;
    pq.push({0, 1});

    while(!pq.empty()){
        auto [w, v] = pq.top(); pq.pop();
        if(vis[v]) continue;
        vis[v] = true;

        for(auto [u, wt]: graph[v]){
            if(!vis[u] && wt < key[u]){
                key[u] = wt;
                p[u] = v;
                pq.push({wt, u});
            } 
        }
    }

    LL cost = 0;
    for(int i =1; i<=n; i++){
        if(key[i] == INF) return -INF;
        cost+= key[i];
    }

    return cost;
}