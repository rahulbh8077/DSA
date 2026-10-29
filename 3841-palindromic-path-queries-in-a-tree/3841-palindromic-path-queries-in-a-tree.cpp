class Solution {
public:
    struct SegTree {
        int n;
        vector<int> tree, lazy;

        SegTree(const vector<int>& a) {
            n = a.size();
            tree.resize(4 * n);
            lazy.resize(4 * n, 0);
            build(1, 0, n - 1, a);
        }

        void build(int p, int l, int r, const vector<int>& a) {
            if (l == r) {
                tree[p] = a[l];
                return;
            }

            int m = (l + r) / 2;
            build(p * 2, l, m, a);
            build(p * 2 + 1, m + 1, r, a);

            tree[p] = tree[p * 2] ^ tree[p * 2 + 1];
        }

        void apply(int p, int x) {
            // XOR x for every element in this segment.
            // We only care about parity, so for a segment
            // of odd length the XOR survives.
            lazy[p] ^= x;
        }

        void push(int p, int l, int r) {
            if (lazy[p] == 0)
                return;

            int m = (l + r) / 2;
            int x = lazy[p];

            if ((m - l + 1) & 1)
                tree[p * 2] ^= x;

            if ((r - m) & 1)
                tree[p * 2 + 1] ^= x;

            lazy[p * 2] ^= x;
            lazy[p * 2 + 1] ^= x;

            lazy[p] = 0;
        }

        void update(int ql, int qr, int x) {
            update(1, 0, n - 1, ql, qr, x);
        }

        void update(int p, int l, int r,
                   int ql, int qr, int x) {

            if (ql <= l && r <= qr) {
                if ((r - l + 1) & 1)
                    tree[p] ^= x;

                lazy[p] ^= x;
                return;
            }

            push(p, l, r);

            int m = (l + r) / 2;

            if (ql <= m)
                update(p * 2, l, m, ql, qr, x);

            if (qr > m)
                update(p * 2 + 1, m + 1, r, ql, qr, x);

            tree[p] = tree[p * 2] ^ tree[p * 2 + 1];
        }

        int query(int ql, int qr) {
            return query(1, 0, n - 1, ql, qr);
        }

        int query(int p, int l, int r,
                  int ql, int qr) {

            if (ql <= l && r <= qr)
                return tree[p];

            push(p, l, r);

            int m = (l + r) / 2;
            int ans = 0;

            if (ql <= m)
                ans ^= query(p * 2, l, m, ql, qr);

            if (qr > m)
                ans ^= query(p * 2 + 1, m + 1, r, ql, qr);

            return ans;
        }
    };

    int n;
    vector<vector<int>> graph;
    vector<int> tin, tout, depth;
    vector<vector<int>> up;
    int timer;

    void dfs(int u, int p) {
        tin[u] = timer++;

        up[0][u] = p;

        for (int k = 1; k < (int)up.size(); k++)
            up[k][u] = up[k - 1][up[k - 1][u]];

        for (int v : graph[u]) {
            if (v == p)
                continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer - 1;
    }

    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (isAncestor(u, v))
            return u;

        if (isAncestor(v, u))
            return v;

        for (int k = (int)up.size() - 1; k >= 0; k--) {
            if (!isAncestor(up[k][u], v))
                u = up[k][u];
        }

        return up[0][u];
    }

    int mask(char c) {
        return 1 << (c - 'a');
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;

        graph.assign(n, {});

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);

        int LOG = 1;

        while ((1 << LOG) <= n)
            LOG++;

        up.assign(LOG, vector<int>(n));

        timer = 0;

        // Root the tree at 0.
        dfs(0, 0);

        /*
            pref[u] = XOR of characters from root to u.

            For a path u -> v:

            pref[u] XOR pref[v] XOR char(lca)

            gives the parity mask of the path.
        */

        vector<int> pref(n);

        function<void(int,int,int)> buildPrefix =
            [&](int u, int p, int cur) {

                cur ^= mask(s[u]);
                pref[u] = cur;

                for (int v : graph[u]) {
                    if (v != p)
                        buildPrefix(v, u, cur);
                }
            };

        buildPrefix(0, -1, 0);

        /*
            Instead of directly storing prefix masks, we use
            a lazy segment tree.

            When node u changes x -> y, every node in u's
            subtree has its root-prefix mask changed by:

                mask(x) XOR mask(y)

            Euler tour makes every subtree a contiguous interval.
        */

        vector<int> euler(n);

        for (int u = 0; u < n; u++)
            euler[tin[u]] = pref[u];

        SegTree st(euler);

        vector<bool> answer;

        for (string &q : queries) {
            string type;
            string a, b;

            stringstream ss(q);
            ss >> type >> a >> b;

            if (type == "update") {
                int u = stoi(a);
                char newChar = b[0];

                int change = mask(s[u]) ^ mask(newChar);

                // Every prefix inside u's subtree changes.
                st.update(tin[u], tout[u], change);

                s[u] = newChar;
            }
            else {
                int u = stoi(a);
                int v = stoi(b);

                int w = lca(u, v);

                int pathMask =
                    st.query(tin[u], tin[u]) ^
                    st.query(tin[v], tin[v]) ^
                    mask(s[w]);

                /*
                    At most one character may have odd frequency.

                    x == 0       -> 0 odd characters
                    x & (x - 1)  -> remove lowest set bit
                    Therefore <= 1 set bit iff:
                        x & (x - 1) == 0
                */

                answer.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return answer;
    }
};