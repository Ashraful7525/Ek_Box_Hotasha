//*Seive Algo for finding primes*//
// computes primes upto 1e9 in 3sec

const int MAXPR = (int)(1e6+5);
vector<int> primes;

void calcPrimes() {
    primes.push_back(2);
    auto sum = 2LL;
    int cnt = 1;
 
    const int S = round(sqrt(MAXPR));
    vector<char> sieve(S + 1, true);
    vector<array<int, 2>> cp;
    for (int i = 3; i < S; i += 2) {
        if (!sieve[i])
            continue;
        cp.push_back({i, (i * i - 1) / 2});
        for (int j = i * i; j <= S; j += 2 * i)
            sieve[j] = false;
    }
    vector<char> block(S);
    int high = (MAXPR - 1) / 2;
    for (int low = 0; low <= high; low += S) {
        fill(block.begin(), block.end(), true);
        for (auto &i : cp) {
            int p = i[0], idx = i[1];
            for (; idx < S; idx += p)
                block[idx] = false;
            i[1] = idx - S;
        }
        if (low == 0)
            block[0] = false;
        for (int i = 0; i < S && low + i <= high; i++){
            if (block[i]){
                ++cnt, sum += (low + i) * 2 + 1;
                primes.push_back((low + i) * 2 + 1);

            }
        }
    }
}