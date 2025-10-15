LL FloorSumAP(LL a, LL b, LL c, LL n){
    if(!a) return (b / c)*(n + 1);
    if(a >= c or b >= c) return ((n * (n + 1))/ 2) * (a / c) + (n + 1) * (b / c) + FloorSumAP(a % c, b % c, c, n);
    LL m = (a * n + b) / c;
    return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
}

LL binpow(LL a, LL b) {
    if (b == 0) return 1;
    LL res = binpow(a, b / 2);
    if (b % 2) return res * res * a;
    else return res * res;
}

LL inv(LL a, LL m) {
  return a <= 1 ? a : m - (long long)(m/a) * inv(m % a, m) % m;
}