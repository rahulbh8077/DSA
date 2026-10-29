class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        // Handle zero
        if (numerator == 0)
            return "0";

        string ans;

        // Check whether the result is negative
        if ((numerator < 0) ^ (denominator < 0))
            ans += "-";

        // Convert to long long to avoid overflow
        long long num = numerator;
        long long den = denominator;

        num = llabs(num);
        den = llabs(den);

        // Integer part
        ans += to_string(num / den);

        long long rem = num % den;

        // No fractional part
        if (rem == 0)
            return ans;

        ans += ".";

        // remainder -> position in ans
        unordered_map<long long, int> mp;

        while (rem != 0) {

            // Repeated remainder means repeating decimal
            if (mp.count(rem)) {
                ans.insert(mp[rem], "(");
                ans += ")";
                break;
            }

            mp[rem] = ans.size();

            rem *= 10;

            ans += to_string(rem / den);

            rem %= den;
        }

        return ans;
    }
};