class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();

        vector<long long> squares;

        for (long long x : nums) {
            squares.push_back(x * x);
        }

        sort(squares.begin(), squares.end());

        long long ans = 0;

        // Smaller half is subtracted
        for (int i = 0; i < n / 2; i++) {
            ans -= squares[i];
        }

        // Larger half is added
        for (int i = n / 2; i < n; i++) {
            ans += squares[i];
        }

        return ans;
    }
};