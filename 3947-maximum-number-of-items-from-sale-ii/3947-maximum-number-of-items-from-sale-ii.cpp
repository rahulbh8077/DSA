class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);

        int minPrice = INT_MAX;

        // Count frequency of each factor
        for (auto &it : items) {
            freq[it[0]]++;
            minPrice = min(minPrice, it[1]);
        }

        // Calculate eligible free item types
        vector<int> gain(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                gain[i] += freq[j];
            }

            gain[i]--; // Exclude the item itself
        }

        // Store profitable double-value purchases
        vector<pair<int, int>> deals;

        for (auto &it : items) {
            int factor = it[0];
            int price = it[1];

            if (gain[factor] > 0 &&
                1LL * price < 2LL * minPrice) {

                deals.push_back({price, gain[factor]});
            }
        }

        // Cheapest double-value purchases first
        sort(deals.begin(), deals.end());

        long long ans = 0;

        // Buy double-value items
        for (auto &deal : deals) {
            int price = deal.first;
            int count = deal.second;

            long long buy = min(
                (long long)count,
                (long long)budget / price
            );

            ans += buy * 2;
            budget -= buy * price;
        }

        // Spend remaining budget on cheapest single-value items
        ans += budget / minPrice;

        return (int)ans;
    }
};