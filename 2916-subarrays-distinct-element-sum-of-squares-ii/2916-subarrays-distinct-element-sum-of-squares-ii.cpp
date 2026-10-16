class Solution {
public:
    static const long long MOD = 1000000007;

    struct Node {
        long long sum = 0;
        long long sumSq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;

        tree[node].sumSq = (
            tree[node].sumSq
            + 2LL * val % MOD * tree[node].sum % MOD
            + len % MOD * val % MOD * val % MOD
        ) % MOD;

        tree[node].sum =
            (tree[node].sum + len % MOD * val) % MOD;

        tree[node].lazy =
            (tree[node].lazy + val) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = (l + r) / 2;

        apply(node * 2, l, mid, tree[node].lazy);
        apply(node * 2 + 1, mid + 1, r, tree[node].lazy);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, long long val) {

        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r, ql, qr, val);

        tree[node].sum =
            (tree[node * 2].sum +
             tree[node * 2 + 1].sum) % MOD;

        tree[node].sumSq =
            (tree[node * 2].sumSq +
             tree[node * 2 + 1].sumSq) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        tree.resize(4 * n + 5);

        unordered_map<int, int> last;

        long long ans = 0;

        for (int r = 0; r < n; r++) {

            int x = nums[r];

            int prev = -1;

            if (last.count(x))
                prev = last[x];

            // Distinct count increases by 1
            // for starting positions [prev + 1, r]
            update(1, 0, n - 1, prev + 1, r, 1);

            last[x] = r;

            // All subarrays ending at r
            ans = (ans + tree[1].sumSq) % MOD;
        }

        return ans;
    }
};