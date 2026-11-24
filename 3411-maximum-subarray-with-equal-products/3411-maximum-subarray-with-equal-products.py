
from math import gcd, lcm

class Solution:
    def maxLength(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0

        for i in range(n):
            product = 1
            g = 0
            L = 1

            for j in range(i, n):
                x = nums[j]

                product *= x
                g = gcd(g, x)
                L = lcm(L, x)

                if product == g * L:
                    ans = max(ans, j - i + 1)

        return ans
