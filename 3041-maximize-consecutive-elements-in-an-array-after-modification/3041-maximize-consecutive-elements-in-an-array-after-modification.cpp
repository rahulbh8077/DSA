class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        unordered_map<int, int> dp;
        int ans = 0;

        for (int x : nums) {
            int prev = dp[x];
            int prevMinus = dp[x - 1];
            int prevPlus = dp[x + 1];

            dp[x] = max(dp[x], prevMinus + 1);
            dp[x + 1] = max(dp[x + 1], prev + 1);

            ans = max(ans, max(dp[x], dp[x + 1]));
        }

        return ans;
    }
};