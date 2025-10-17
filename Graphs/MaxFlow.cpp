#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL INF = (1LL<<60);

// both edmond-karp and ford-fulkerson is added
// currently the algo is not memory efficient
struct max_flow{
    int n, s, t;
    vector<vector<LL>> cap, cngd_cap;
    vector<vector<int>> adj;
    vector<bool> vis;

    max_flow(int n, int s, int t){
        this->n = n;
        this->s = s;
        this->t = t;
        cap.assign(n+1, vector<LL>(n+1, 0));
        adj.assign(n+1, {});
    }

    void add_edge(int u, int v, LL c){
        cap[u][v]+= c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    LL dfs(int v, LL cp){
        vis[v] = true;
        if(v == t) return cp;

        for(int u: adj[v]){
            if(!vis[u] && cngd_cap[v][u]){
                LL koto = dfs(u, min(cp, cngd_cap[v][u]));
                if(koto){
                    cngd_cap[v][u] -= koto;
                    cngd_cap[u][v] += koto;
                    return koto;
                }
            }
        }

        return 0;
    }

    LL bfs(){
        vector<int> parent(n+1, 0);
        queue<pair<int, LL>> q;
        q.push({s, INF});
        vis[s] = true;
        LL aug_flow = 0;

        while(!q.empty()){
            auto [u, f] = q.front();
            if(u == t){
                aug_flow = f;
                break;
            }
            q.pop();

            for(int v: adj[u]){
                if(!vis[v] && cngd_cap[u][v]){
                    vis[v] = true;
                    parent[v] = u;
                    q.push({v, min(cngd_cap[u][v], f)});
                }
            }
        }

        int koi_achi = t;
        if(aug_flow){
            while(parent[koi_achi]){
                cngd_cap[parent[koi_achi]][koi_achi]-= aug_flow;
                cngd_cap[koi_achi][parent[koi_achi]]+= aug_flow;
                koi_achi = parent[koi_achi];
            }
        }

        return aug_flow;
    }

    // works in O(V*F);
    LL ford_fulkerson(){
        cngd_cap = cap;
        LL flow = 0;
        while(true){
            vis.assign(n+1, 0);
            LL koto = dfs(s, INF);
            if(!koto) break;
            flow+= koto;
        }

        return flow;
    }

    // works in O(V*E^2)
    LL edmond_karp(){
        cngd_cap = cap;
        LL flow = 0;
        while(true){
            vis.assign(n+1, 0);
            LL koto = bfs();
            if(!koto) break;
            flow+= koto;
        }

        return flow;
    }
};

void solve(){
    int n, m; cin>>n>>m;
    max_flow mf(n, 1, n);

    for(int i = 1; i<=m; i++){
        int u, v, c; cin>>u>>v>>c;
        mf.add_edge(u, v, c);
    }

    cout<<mf.edmond_karp()<<'\n';

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   
    LL T = 1; //cin>>T;
    while (T--) solve();
    return 0;
}