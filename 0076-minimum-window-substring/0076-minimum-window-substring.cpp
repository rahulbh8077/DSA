class Solution {
public:
    string minWindow(string s, string t) {

        if (s.empty() || t.empty())
            return "";

        // Frequency required for each character
        unordered_map<char, int> need;

        for (char c : t) {
            need[c]++;
        }

        // Frequency of characters in current window
        unordered_map<char, int> window;

        int left = 0;

        // Number of characters from t
        // currently satisfied in the window
        int have = 0;

        int required = need.size();

        int minLen = INT_MAX;
        int start = 0;

        for (int right = 0; right < s.size(); right++) {

            char c = s[right];

            window[c]++;

            // Character requirement is completely satisfied
            if (need.count(c) &&
                window[c] == need[c]) {

                have++;
            }

            // Window is valid
            while (have == required) {

                // Update minimum window
                if (right - left + 1 < minLen) {

                    minLen = right - left + 1;
                    start = left;
                }

                char leftChar = s[left];

                window[leftChar]--;

                // Removing this character makes
                // the window invalid
                if (need.count(leftChar) &&
                    window[leftChar] < need[leftChar]) {

                    have--;
                }

                left++;
            }
        }

        if (minLen == INT_MAX)
            return "";

        return s.substr(start, minLen);
    }
};