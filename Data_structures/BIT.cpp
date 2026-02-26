//0-based indexing
template<typename T>
struct BIT{
    int n; vector<T> t;
 
    BIT(int n): n(n), t(n, T(0)) {}
    //delta means kototuk barse
    void update(LL i, T delta) {
        while(i < n){
            t[i]+= delta;
            i|= (i + 1);
        }
    }
    //0 theke r-th index porzonto sobar zogfol
    T sum(int r) const {
        if(r < 0) return 0;
        T zogfol = 0;
        while(r >= 0){
            zogfol+= t[r];
            r&= (r + 1); r--;
        }
        return zogfol;
    }
    //finds the first occerence where the pref sum is >= k
    int find_sum_K(T k) const {
        int id = -1, pw = 1;
        while((pw << 1) < n) pw<<= 1;
        for(; pw; pw>>= 1){
            int next = id + pw;
            if(next < n && t[next] < k){
                k-= t[next];
                id+= pw;
            }
        }
        return ++id;
    }

    T query(int l, int r) const { return sum(r) -  sum(l-1); }
 
};

template<typename T>
struct BIT2D{
    int n, m; vector<vector<T>> t;
    //row  - n, coloumn - m
    BIT2D(int n, int m): n(n), m(m), t(n, vector<T>(m, T(0))) {}
 
    void update(int x, int y, T delta){
        if(x < 0 || y < 0) return;
        while(x < n){
            int Y = y;
            while(Y < m){
                t[x][Y]+= delta;
                Y = (Y + 1) | Y;
            }
            x = (x + 1) | x;
        }
    }
 
    T sum(int x, int y) const {
        if(x < 0 || y < 0) return 0;
        T sum = 0;
        while(x >= 0){
            int Y = y;
            while(Y >= 0){
                sum+= t[x][Y];
                Y = ((Y+1) & Y) - 1;
            }
            x = ((x + 1) & x) - 1;
        }
        return sum;
    }
 
    T query(int x1, int y1, int x2, int y2) const { return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1); }
};