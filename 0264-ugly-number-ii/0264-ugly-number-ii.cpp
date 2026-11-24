
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<long long> dp(n);

        dp[0] = 1;

        int i2 = 0, i3 = 0, i5 = 0;

        for (int i = 1; i < n; i++) {
            long long a = dp[i2] * 2;
            long long b = dp[i3] * 3;
            long long c = dp[i5] * 5;

            dp[i] = min({a, b, c});

            if (dp[i] == a) i2++;
            if (dp[i] == b) i3++;
            if (dp[i] == c) i5++;
        }

        return dp[n - 1];
    }
};
