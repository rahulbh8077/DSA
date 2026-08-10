class Solution {
public:
    int largestElement(vector<int>& nums) {
        int large = nums[0];

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > large) {
                large = nums[i];
            }
        }

        return large;
    }
};
// Brute force approach is used in solving this problem. 
