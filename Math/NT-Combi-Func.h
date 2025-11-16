const int mod = 998244353;

//finds a^b modulo mod
LL binpow(LL a, LL b) {
    if (b == 0) return 1;
    LL res = binpow(a, b / 2);
    if (b % 2) return res * res * a;
    else return res * res;
}
 
//computes modular inverse of a modulo m (a and m must be coprime)
LL inv(LL a, LL m) {
  return a <= 1 ? a : m - (long long)(m/a) * inv(m % a, m) % m;
}


// precalc and func for nCr
const int N = 2e5+10;
LL fact[N], invfact[N];
 
void calc(){
    fact[0] = 1;
    for(int i  =1; i<N; i++){
        fact[i] = fact[i-1] * i % mod;
    }
 
    invfact[N-1] = inv(fact[N-1], mod);
    for(int i = N-2; i>=0; i--){
        invfact[i] = invfact[i+1] * (i+1) % mod;
    }
}
 
LL nCr(int n, int r){
    if(r < 0) return 0;
    if(n < 0) return 0;
    if(n < r) return 0;
    return fact[n] * invfact[n - r] % mod * invfact[r] % mod;
}