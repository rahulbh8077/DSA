class Solution {
public:
    static const int MOD = 1000000007;

    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[j][0] = ways arriving from the left
        // dp[j][1] = ways arriving from above
        vector<array<long long, 2>> dp(n + 1, {0, 0});

        // Starting cell
        dp[1][0] = 1;
        dp[1][1] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Skip starting cell
                if (i == 0 && j == 0)
                    continue;

                long long fromLeft = dp[j][0];
                long long fromAbove = dp[j + 1][1];

                if (grid[i][j] == 0) {
                    // Normal cell
                    long long ways = (fromLeft + fromAbove) % MOD;

                    dp[j + 1][0] = ways;
                    dp[j + 1][1] = ways;
                }
                else {
                    // Mirror:
                    // left -> down
                    // above -> right

                    dp[j + 1][0] = fromAbove;
                    dp[j + 1][1] = fromLeft;
                }
            }
        }

        return dp[n][0];
    }
};