class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        // 1. Already sorted
        bool sorted = true;

        for (int i = 1; i < n; i++) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }

        if (sorted)
            return 0;

        // 2. For an unsorted string of length 2,
        // the only proper substrings have length 1,
        // so nothing can be changed.
        if (n == 2)
            return -1;

        // Minimum and maximum characters
        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        // 3. Minimum is already at the beginning
        // OR maximum is already at the end.
        // Sort the remaining proper substring.
        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        // 4. Minimum or maximum is somewhere in the middle.
        // We can bring it to the correct side in one operation,
        // then finish with another operation.
        for (int i = 1; i < n - 1; i++) {
            if (s[i] == mn || s[i] == mx)
                return 2;
        }

        // 5. Neither min nor max is in the middle.
        // This is the worst case.
        return 3;
    }
};