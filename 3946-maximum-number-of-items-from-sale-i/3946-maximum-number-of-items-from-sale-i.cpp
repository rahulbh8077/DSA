class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = INT_MAX;

        for (auto &item : items) {
            minPrice = min(minPrice, item[1]);
        }

        // dp[j] = maximum items obtained by spending exactly j
        vector<int> dp(budget + 1, -1e9);
        dp[0] = 0;

        for (auto &item : items) {
            int factor = item[0];
            int price = item[1];

            // Count purchased item + free items
            int cnt = 0;

            for (auto &other : items) {
                if (other[0] % factor == 0) {
                    cnt++;
                }
            }

            // 0/1 Knapsack: each item type activates only once
            for (int j = budget; j >= price; j--) {
                dp[j] = max(dp[j], dp[j - price] + cnt);
            }
        }

        int ans = 0;

        // Spend remaining budget on cheapest items
        for (int j = 0; j <= budget; j++) {
            if (dp[j] >= 0) {
                ans = max(ans, dp[j] + (budget - j) / minPrice);
            }
        }

        return ans;
    }
};