class Solution {
public:
    int divide(int dividend, int divisor) {
        // Overflow case
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;

        // Determine the sign
        bool negative = (dividend < 0) ^ (divisor < 0);

        // Convert to long long and absolute values
        long long a = llabs((long long)dividend);
        long long b = llabs((long long)divisor);

        long long result = 0;

        while (a >= b) {
            long long temp = b;
            long long multiple = 1;

            // Find the largest doubled divisor
            while ((temp << 1) <= a) {
                temp <<= 1;
                multiple <<= 1;
            }

            // Subtract it from dividend
            a -= temp;
            result += multiple;
        }

        if (negative)
            result = -result;

        // Clamp to 32-bit integer range
        if (result > INT_MAX)
            return INT_MAX;

        if (result < INT_MIN)
            return INT_MIN;

        return (int)result;
    }
};