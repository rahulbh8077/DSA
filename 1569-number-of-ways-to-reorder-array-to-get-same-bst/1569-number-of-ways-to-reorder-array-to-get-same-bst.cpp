class Solution {
public:
    static const long long MOD = 1000000007;

    long long comb[1005][1005];

    long long solve(vector<int>& nums) {
        int n = nums.size();

        // A single node has only one ordering
        if (n <= 2)
            return 1;

        int root = nums[0];

        vector<int> left;
        vector<int> right;

        // Divide elements according to BST property
        for (int i = 1; i < n; i++) {
            if (nums[i] < root)
                left.push_back(nums[i]);
            else
                right.push_back(nums[i]);
        }

        // Number of valid arrangements of left and right subtrees
        long long leftWays = solve(left);
        long long rightWays = solve(right);

        // Choose positions for left subtree elements
        long long waysToMerge =
            comb[left.size() + right.size()][left.size()];

        return (((waysToMerge * leftWays) % MOD) * rightWays) % MOD;
    }

    int numOfWays(vector<int>& nums) {

        int n = nums.size();

        // Compute combinations using Pascal's triangle
        for (int i = 0; i <= n; i++) {
            comb[i][0] = comb[i][i] = 1;

            for (int j = 1; j < i; j++) {
                comb[i][j] =
                    (comb[i - 1][j - 1] +
                     comb[i - 1][j]) % MOD;
            }
        }

        // solve() includes the original ordering
        return (solve(nums) - 1 + MOD) % MOD;
    }
};