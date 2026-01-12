LL FloorSumAP(LL a, LL b, LL c, LL n){
    if(!a) return (b / c)*(n + 1);
    if(a >= c or b >= c) return ((n * (n + 1))/ 2) * (a / c) + (n + 1) * (b / c) + FloorSumAP(a % c, b % c, c, n);
    LL m = (a * n + b) / c;
    return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
}
