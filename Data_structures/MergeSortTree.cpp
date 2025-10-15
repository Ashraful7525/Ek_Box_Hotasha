//this is an unusual version of merge sort tree, you need to edit the query and other func to do your work

struct mergesorttree{
    pair<int, int> dummy = {-1, -1};
    int n;
    vector<multiset<int>> s;

    mergesortx(int n){
        this->n = n;
        s.assign((n<<2), multiset<int>());
    }

    void insert(int id, int st, int end, int index, int x){
        s[id].insert(x);
        if(st == end) return;
        
        int mid = ((st + end)>>1);
        if(st <= index && index <= mid) insert((id<<1), st, mid, index, x);
        if(mid + 1 <= index && index <= end) insert((id<<1)+1, mid+1, end, index, x);  
    }

    void erase(int id, int st, int end, int index, int x){
        s[id].erase(s[id].find(x));
        if(st == end) return;
        
        int mid = ((st + end)>>1);
        if(st <= index && index <= mid) erase((id<<1), st, mid, index, x);
        if(mid + 1 <= index && index <= end) erase((id<<1)+1, mid+1, end, index, x);  
    }

    pair<int, int> query(int id, int st, int end, int l, int r, int x){
        if(end <  l || r < st) return dummy;
        if(s[id].upper_bound(x) == s[id].end()) return dummy;
        if(st == end){
            auto it = s[id].upper_bound(x);
            pair<int, int> p = {st, (*it)};
            return p;
        }
        
        int mid = ((st + end)>>1);
        pair<int, int> p = query((id<<1), st, mid, l, r, x);
        if(p != dummy) return p;

        p = query((id<<1)+1, mid+1, end, l, r, x);
        return p;
    }

    void insert(int index, int val){
        insert(1, 1, n, index, val);
    }

    void erase(int index, int val){
        erase(1, 1, n, index, val);
    }

    pair<int, int> query(int l, int r, int x){
        return query(1, 1, n, l, r, x);
    }
};