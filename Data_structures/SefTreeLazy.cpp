//1-based indexing
struct segment_tree{
    const LL INF = 1LL<<60;
    int n; vector<LL> val, lazy;
 
    segment_tree(vector<LL> &v){
        n = v.size() - 1;
        val.assign(4*n + 4, INF);
        lazy.assign(4*n + 4, 0);
        build(1, 1, n, v);
    }
 
    void push(int id, int st, int end){
        val[2 * id] += lazy[id];
        val[2 * id + 1] += lazy[id];
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
        lazy[id] = 0;
    }
 
    void build(int id, int st, int end, vector<LL> &v){
        if(st == end){
            val[id] = v[st];
            return;
        }
        int mid = (st + end)/2;
        build(2*id, st, mid, v);
        build(2*id+1, mid+1, end, v);
        val[id] = min(val[2*id], val[2*id + 1]);
    }
 
    LL query(int id, int st, int end, int l, int r){
        if(end < l || r < st) return INF;
        if(l<= st  && end<=r) return val[id];

        push(id, st, end);
        int mid = (st + end)/2;
        LL leftmin = query(2*id, st, mid, l, r); 
        LL rightmin = query(2*id+1, mid+1, end, l, r);
        return min(leftmin, rightmin);
    }
  
    void update(int id, int st, int end, int l, int r, LL x){
        if(end < l || r < st) return;
        if(l <= st && end <= r){
            lazy[id] += x;
            val[id] += x;
            return;
        }

        push(id, st, end);
        int mid = (st+ end)/2;
        update(2*id, st, mid, l, r, x);
        update(2*id + 1, mid + 1, end, l, r, x);
        val[id] = min(val[2*id], val[2*id+ 1]);
    }

    LL query(int l , int r) {return query(1, 1, n, l, r); }
    void update(int l, int r, LL x) {update(1, 1, n, l, r, x); }
 
};