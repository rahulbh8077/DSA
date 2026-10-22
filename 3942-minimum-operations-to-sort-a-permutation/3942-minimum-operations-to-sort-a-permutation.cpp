class Solution {
public:

    // Check whether nums is a cyclic rotation of
    // [0, 1, 2, ..., n-1].
    // Returns k such that nums = left rotation by k,
    // otherwise returns -1.
    int increasingRotation(vector<int>& nums) {
        int n = nums.size();

        int pos = 0;

        // Find position of 0
        while (pos < n && nums[pos] != 0) {
            pos++;
        }

        // Check circularly: 0,1,2,3,...,n-1
        for (int i = 0; i < n; i++) {
            if (nums[(pos + i) % n] != i) {
                return -1;
            }
        }

        return pos;
    }

    // Check whether nums is a cyclic rotation of
    // [n-1, n-2, ..., 1, 0].
    //
    // Returns k such that:
    // nums = left rotation of decreasing array by k.
    int decreasingRotation(vector<int>& nums) {
        int n = nums.size();

        int pos = 0;

        // Find position of n-1
        while (pos < n && nums[pos] != n - 1) {
            pos++;
        }

        // Check circularly:
        // n-1, n-2, ..., 1, 0
        for (int i = 0; i < n; i++) {
            int expected = n - 1 - i;

            if (nums[(pos + i) % n] != expected) {
                return -1;
            }
        }

        // If the decreasing array is:
        // [n-1, n-2, ..., 0]
        //
        // and we left rotate it k times,
        // n-1 moves to position n-k.
        int k = (n - pos) % n;

        return k;
    }

    int minOperations(vector<int>& nums) {
        int n = nums.size();

        if (n <= 1)
            return 0;

        int ans = INT_MAX;

        // ------------------------------------------------
        // CASE 1:
        // nums is a rotation of:
        // [0,1,2,...,n-1]
        // ------------------------------------------------

        int k = increasingRotation(nums);

        if (k != -1) {

            // Directly use k left rotations.
            //
            // OR:
            // use two reversals + (n-k) left rotations
            // to simulate the opposite direction.
            //
            // Example:
            // R + L^x + R = right rotation by x
            int cost = min(k, n - k + 2);

            ans = min(ans, cost);
        }

        // ------------------------------------------------
        // CASE 2:
        // nums is a rotation of:
        // [n-1,n-2,...,0]
        // ------------------------------------------------

        k = decreasingRotation(nums);

        if (k != -1) {

            // One reversal changes the decreasing
            // sequence into the increasing sequence.
            //
            // Then we need k rotations.
            //
            // We can also rotate in the other direction.
            int cost = 1 + min(k, n - k);

            ans = min(ans, cost);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};