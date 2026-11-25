from typing import List

class Solution:
    def smallestUniqueSubarray(self, nums: List[int]) -> int:
        n = len(nums)

        if n == 0:
            return 0

        # Coordinate compression
        vals = sorted(set(nums))
        mp = {v: i + 1 for i, v in enumerate(vals)}

        # Add a unique smallest sentinel
        s = [mp[x] for x in nums] + [0]
        N = n + 1

        # Initial sorting
        p = sorted(range(N), key=s.__getitem__)

        c = [0] * N
        classes = 1

        for i in range(1, N):
            if s[p[i]] != s[p[i - 1]]:
                classes += 1
            c[p[i]] = classes - 1

        # Build suffix array using doubling
        h = 0

        while (1 << h) < N:
            shift = 1 << h

            pn = [(x - shift) % N for x in p]

            cnt = [0] * classes

            for x in pn:
                cnt[c[x]] += 1

            pos = [0] * classes

            for i in range(1, classes):
                pos[i] = pos[i - 1] + cnt[i - 1]

            pnew = [0] * N

            for x in pn:
                cl = c[x]
                pnew[pos[cl]] = x
                pos[cl] += 1

            p = pnew

            cn = [0] * N
            new_classes = 1

            for i in range(1, N):
                cur = (
                    c[p[i]],
                    c[(p[i] + shift) % N]
                )

                prev = (
                    c[p[i - 1]],
                    c[(p[i - 1] + shift) % N]
                )

                if cur != prev:
                    new_classes += 1

                cn[p[i]] = new_classes - 1

            c = cn
            classes = new_classes
            h += 1

        sa = p[1:]

        # Build inverse suffix array
        pos = [0] * n

        for r, i in enumerate(sa):
            pos[i] = r

        # Kasai's LCP algorithm
        lcp = [0] * n
        k = 0

        for i in range(n):
            r = pos[i]

            if r == 0:
                continue

            j = sa[r - 1]

            while i + k < n and j + k < n:
                if nums[i + k] != nums[j + k]:
                    break
                k += 1

            lcp[r] = k

            if k:
                k -= 1

        # Find the shortest unique subarray
        ans = n

        for r, i in enumerate(sa):
            mx = 0

            if r > 0:
                mx = lcp[r]

            if r + 1 < n:
                mx = max(mx, lcp[r + 1])

            length = mx + 1

            if i + length <= n:
                ans = min(ans, length)

        return ans