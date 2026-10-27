class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();

        if (n <= 2)
            return n;

        int ans = 0;

        for (int i = 0; i < n; i++) {
            map<pair<int, int>, int> mp;

            int localMax = 0;

            for (int j = i + 1; j < n; j++) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                // Reduce slope to simplest form
                int g = gcd(abs(dx), abs(dy));

                dx /= g;
                dy /= g;

                // Keep the sign consistent
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                }

                // Vertical line
                if (dx == 0)
                    dy = 1;

                // Horizontal line
                if (dy == 0)
                    dx = 1;

                mp[{dy, dx}]++;

                localMax = max(localMax, mp[{dy, dx}]);
            }

            // +1 for the starting point
            ans = max(ans, localMax + 1);
        }

        return ans;
    }
};