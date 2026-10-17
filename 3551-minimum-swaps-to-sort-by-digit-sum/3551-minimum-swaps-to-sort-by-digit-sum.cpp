class Solution {
public:

    int digitSum(int x) {
        int sum = 0;

        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }

        return sum;
    }

    int minSwaps(vector<int>& nums) {

        int n = nums.size();

        // Store {digit sum, number, original index}
        vector<tuple<int, int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({
                digitSum(nums[i]),
                nums[i],
                i
            });
        }

        // Sort according to:
        // 1. digit sum
        // 2. number
        sort(arr.begin(), arr.end());

        // target[i] = original index of the element
        // that should be at position i
        vector<int> target(n);

        for (int i = 0; i < n; i++) {
            target[i] = get<2>(arr[i]);
        }

        vector<bool> visited(n, false);

        int swaps = 0;

        // Find cycles
        for (int i = 0; i < n; i++) {

            if (visited[i] || target[i] == i)
                continue;

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = target[j];
                cycleSize++;
            }

            // A cycle of size k requires k - 1 swaps
            swaps += cycleSize - 1;
        }

        return swaps;
    }
};