class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums;

        // Store numbers 1 to n
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }

        // factorial = (n-1)!
        int factorial = 1;
        for (int i = 1; i < n; i++) {
            factorial *= i;
        }

        // Convert k to 0-based indexing
        k--;

        string ans = "";

        for (int i = n; i > 0; i--) {
            
            // Find which block k belongs to
            int index = k / factorial;

            // Add selected number
            ans += to_string(nums[index]);

            // Remove selected number
            nums.erase(nums.begin() + index);

            // Update k
            k %= factorial;

            // Update factorial
            if (i > 1) {
                factorial /= (i - 1);
            }
        }

        return ans;
    }
};