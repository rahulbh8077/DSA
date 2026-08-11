class Solution {
public:
    int secondLargestElement(vector<int>& nums) {
        int large = nums[0];
        int second = -1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > large) {
                second = large;
                large = nums[i];
            }
            else if (nums[i] > second && nums[i] != large) {
                second = nums[i];
            }
        }

        return second;
    }
};
