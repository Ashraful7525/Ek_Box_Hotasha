//finds a xor basis such that each term is from v

vector<int> xorBasis(const vector<int>& v) {
    const int BITS = 32;
    vector<int> basis(BITS, 0);
    vector<int> orig(BITS, 0);
    for (int x : v) {
        int cur = x;
        for (int i = BITS - 1; i >= 0; i--) {
            if (!(cur & (1 << i))) continue;
            if (!basis[i]) {
                basis[i] = cur;
                orig[i] = x;
                break;
            }
            cur ^= basis[i];
        }
    }
    vector<int> result;
    for (int i = 0; i < BITS; i++) {
        if (orig[i] != 0)
            result.push_back(orig[i]);
    }
    return result;
}