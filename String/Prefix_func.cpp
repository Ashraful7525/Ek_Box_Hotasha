// PI-function or prefix function 

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> Z_function(const string &s) {
    int n = s.size();
    vector<int> Z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if(i < r) Z[i] = min(r - i, Z[i - l]);
        while(i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) Z[i]++;
        if(i + Z[i] > r){
            l = i;
            r = i + Z[i];
        }
    }
    return Z;
}