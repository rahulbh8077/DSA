
class Solution {
    using ll = long long;

    struct Fenwick {
        int n;
        vector<ll> bit;

        Fenwick(int n) : n(n), bit(n + 1, 0) {}

        void update(int i, ll val) {
            while (i <= n) {
                bit[i] += val;
                i += i & -i;
            }
        }

        ll query(int i) {
            ll res = 0;
            while (i > 0) {
                res += bit[i];
                i -= i & -i;
            }
            return res;
        }

        int kth(ll k) {
            int idx = 0;
            int pw = 1;
            while ((pw << 1) <= n) pw <<= 1;

            for (; pw; pw >>= 1) {
                int nxt = idx + pw;
                if (nxt <= n && bit[nxt] < k) {
                    idx = nxt;
                    k -= bit[nxt];
                }
            }
            return idx + 1;
        }
    };

public:
    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        vector<int> a = nums;
        sort(a.begin(), a.end());

        a.erase(unique(a.begin(), a.end()), a.end());

        int m = a.size();

        vector<int> id(n);

        for (int i = 0; i < n; i++) {
            id[i] = lower_bound(
                a.begin(), a.end(), nums[i]
            ) - a.begin() + 1;
        }

        Fenwick freq(m), sums(m);

        auto add = [&](int i, int sign) {
            freq.update(id[i], sign);
            sums.update(id[i], 1LL * sign * nums[i]);
        };

        auto getCost = [&]() -> ll {

            int midPos = (x + 1) / 2;

            int p = freq.kth(midPos);
            ll median = a[p - 1];

            ll lc = freq.query(p);
            ll ls = sums.query(p);

            ll total = sums.query(m);
            ll rc = x - lc;
            ll rs = total - ls;

            return median * lc - ls
                 + rs - median * rc;
        };

        vector<ll> cost(n - x + 1);

        // Calculate cost of every window
        for (int i = 0; i < n; i++) {

            add(i, 1);

            if (i >= x) {
                add(i - x, -1);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        const ll INF = LLONG_MAX / 4;

        vector<ll> prev(n + 1, 0);
        vector<ll> curr(n + 1, INF);

        // DP
        for (int j = 1; j <= k; j++) {

            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Skip current element
                curr[i] = curr[i - 1];

                // Select a subarray of size x
                if (i >= x && prev[i - x] != INF) {

                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
