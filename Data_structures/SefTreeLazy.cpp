//1-based indexing
 
struct segment_tree{
    LL n;
    vector<LL> val;
    vector<LL> lazy;
 
    segment_tree(vector<LL> &v){
        n = v.size();
        val.assign(4*n, INF);
        lazy.assign(4*n, 0);
        build(1, 1, n, v);
    }
 
    void push(LL id, LL st, LL end){
        if(lazy[id] != 0){
            val[id] += lazy[id];
            if(st != end){
                lazy[2*id] += lazy[id];
                lazy[2*id + 1] += lazy[id];
            }
            lazy[id] = 0;
        }
    }
 
    void build(LL id, LL st, LL end, vector<LL> &v){
        if(st == end){
            val[id] = v[st];
            return;
        }
 
        LL mid = (st + end)/2;
        build(2*id, st, mid, v);
        build(2*id+1, mid+1, end, v);
 
        val[id] = min(val[2*id], val[2*id + 1]);
    }
 
    LL query(LL id, LL st, LL end, LL l, LL r){
        push(id, st, end);
        if(l<= st  && end<=r) return val[id];
        if(end < l || r < st) return INF;
 
        LL mid = (st + end)/2;
        LL leftmin = query(2*id, st, mid, l, r); 
        LL rightmin = query(2*id+1, mid+1, end, l, r);
 
        return min(leftmin, rightmin);
    }
  
    void update(LL id, LL st, LL end, LL l, LL r, LL x){
        if(l <= st && end <= r){
            lazy[id] += x;
            push(id, st, end);
            return;
        }
 
        if(end < l || r < st) return;
 
        push(id, st, end);
        LL mid = (st+ end)/2;
        update(2*id, st, mid, l, r, x);
        update(2*id + 1, mid + 1, end, l, r, x);
 
        val[id] = min(val[2*id], val[2*id+ 1]);
    }
 
};