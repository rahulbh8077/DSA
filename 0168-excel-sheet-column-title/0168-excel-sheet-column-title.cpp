class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans;

        while (columnNumber > 0) {
            columnNumber--;  // Convert 1-26 into 0-25

            int rem = columnNumber % 26;

            ans += char('A' + rem);

            columnNumber /= 26;
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};