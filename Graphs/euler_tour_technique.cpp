vector<vector<LL>> graph;
vector<LL> intime, outtime;
LL timex = 0;

void dfs(LL v, LL p = 0){
    intime[v] = ++timex;
    for(auto u: graph[v]){
        if(u!= p){
            dfs(u, v);
        }
    }
    outtime[v] = timex;
}