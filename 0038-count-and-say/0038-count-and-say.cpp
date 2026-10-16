class Solution {
public:
    string countAndSay(int n) {
        string s = "1";

        for (int k = 1; k < n; k++) {
            string result = "";

            int i = 0;

            while (i < s.length()) {
                int j = i;

                // Count consecutive same digits
                while (j < s.length() && s[j] == s[i]) {
                    j++;
                }

                // Add count and digit
                result += to_string(j - i);
                result += s[i];

                i = j;
            }

            s = result;
        }

        return s;
    }
};