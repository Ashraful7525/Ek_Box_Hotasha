struct SuffixAutomaton {
    struct State {
        int len, link;
        vector<int> next; // If we're restricted with memory, it's okay to use map
        State(int _len = 0, int alpha = 26) : len(_len), link(-1), next(alpha, -1) {}
    };

    vector<State> st;
    int last;
    static const int ALPHA = 26;

    SuffixAutomaton() {
        st.emplace_back(0, ALPHA);
        st[0].link = -1;
        last = 0;
    }

    void extend(char ch) {
        int c = ch - 'a';
        if (c < 0 || c >= ALPHA) return;

        int cur = (int)st.size();
        st.emplace_back(st[last].len + 1, ALPHA);

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if(p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = (int)st.size();
                st.emplace_back(st[p].len + 1, ALPHA);
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    //build from string
    void build(const string &s) {
        for (char ch : s) extend(ch);
    }
};