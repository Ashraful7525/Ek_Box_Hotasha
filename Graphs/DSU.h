// DSU Algo
// Source : CP Algorithms
struct DSU{
    int n;
    vector<int> parent, sizex;

    DSU(int n){
        this->n = n;
        parent.assign(n+1, 0);
        sizex.resize(n+1, 0);
        for(int i = 1; i<=n; i++) make_set(i);
    }

    void make_set(int v){
        parent[v] = v;
        sizex[v] = 1;
    }

    int find_set(int v){
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if(a != b){
            if (sizex[a] < sizex[b]) swap(a, b);
            parent[b] = a;
            sizex[a] += sizex[b];
        }
    }
};