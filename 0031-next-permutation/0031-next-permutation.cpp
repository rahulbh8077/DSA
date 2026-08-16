class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        
        int n = nums.size();
        int i = n - 2;

        // Step 1: Find the first decreasing element
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // Step 2: Find the element just greater than nums[i]
        if (i >= 0) {
            int j = n - 1;

            while (nums[j] <= nums[i]) {
                j--;
            }

            swap(nums[i], nums[j]);
        }

        // Step 3: Reverse the remaining elements
        reverse(nums.begin() + i + 1, nums.end());
    }
};