//0-based indexing
struct BIT{
    LL n; vector<LL> t;
 
    BIT(LL n){
        this->n = n;
        t.assign(n+1, 0);
    }
    //delta means kototuk barse
    void update(LL i, LL delta){
        while(i < n){
            t[i]+= 1LL*delta;
            i = ((i + 1) | i);
        }
    }
    //0 theke r-th index porzonto sobar zogfol
    LL sum(LL r){
        if(r < 0) return 0;
        LL zogfol = 0;
        while(r >= 0){
            zogfol+= 1LL*t[r];
            r = (r & (r + 1))- 1;
        }
        return zogfol;
    }

    LL query(LL l, LL r){ return sum(r) -  sum(l-1); }
 
};
 
struct BIT2D{
    int n, m; vector<vector<int>> t;
    //row  - n, coloumn - m
    BIT2D(int n, int m){
        this->n = n;
        this->m = m;
        t.assign(n, vector<int>(m, 0));
    }
 
    void update(int x, int y, int delta){
        if(x < 0 || y < 0) return
        while(x < n){
            int Y = y;
            while(Y < m){
                t[x][Y]+= delta;
                Y = (Y + 1) | Y;
            }
            x = (x + 1) | x;
        }
    }
 
    int sum(int x, int y){
        if(x < 0 || y < 0) return 0;
        int sum = 0;
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
 
    int query(int x1, int y1, int x2, int y2){ return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1); }
};