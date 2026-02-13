//1-based indexing
 
struct segment_tree{
    const int INF = 1<<30;
    int n; vector<int> val;

    segment_tree(vector<int> &v){
        n = v.size();
        val.assign(4*n, INF);
        build(1, 1, n, v);
    }
 
    void build(int id, int st, int end, vector<int> &v){
        if(st == end){
            val[id] = v[st];
            return;
        }
        int mid = (st + end)/2;
        build(2*id, st, mid, v);
        build(2*id+1, mid+1, end, v);
        val[id] = min(val[2*id], val[2*id + 1]);
    }
 
    int query(int id, int st, int end, int l, int r){
        if(l<= st  && end<=r) return val[id];
        if(end < l || r < st) return INF;
        int mid = (st + end)/2;
        int leftmin = query(2*id, st, mid, l, r); 
        int rightmin = query(2*id+1, mid+1, end, l, r);
        return min(leftmin, rightmin);
    }
 
    void update(int id, int st, int end, int i, int x){
        if(st == end){
            val[id] = x;
            return;
        }
        int mid = ( st + end)/2;
        if(i <= mid) update(2*id, st, mid, i, x);
        else update(2*id + 1, mid+1, end, i, x);
        val[id] = min(val[2*id], val[2*id+ 1]);
    }

    int query(int l, int r){ return query(1, 1, n, l, r); }
    void update(int i, int x){ update(1, 1, n, i, x); }
 
};