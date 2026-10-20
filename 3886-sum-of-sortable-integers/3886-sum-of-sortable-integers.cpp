class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        // prefix maximum
        vector<int> prefMax(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }

        // suffix minimum
        vector<int> suffMin(n + 1, INT_MAX);

        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(nums[i], suffMin[i + 1]);
        }

        // prefDrop[i] = number of normal descents
        // among positions 0 ... i
        vector<int> prefDrop(n, 0);

        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1];

            if (nums[i - 1] > nums[i]) {
                prefDrop[i]++;
            }
        }

        // Check whether k is sortable
        auto check = [&](int k) -> bool {

            for (int start = 0; start < n; start += k) {

                int end = start + k - 1;

                // Number of descents inside the block
                int drops = prefDrop[end] - prefDrop[start];

                // Check the circular boundary:
                // last element -> first element
                if (nums[end] > nums[start]) {
                    drops++;
                }

                // More than one circular descent
                // means no rotation can sort this block.
                if (drops > 1) {
                    return false;
                }

                // Check boundary between this block
                // and everything after it.
                if (prefMax[start] > suffMin[start]) {
                    return false;
                }
            }

            return true;
        };

        int answer = 0;

        // Only divisors of n can be k.
        for (int i = 1; i <= n / i; i++) {

            if (n % i == 0) {

                // i is a divisor
                if (check(i)) {
                    answer += i;
                }

                // n/i is another divisor
                if (i != n / i && check(n / i)) {
                    answer += n / i;
                }
            }
        }

        return answer;
    }
};