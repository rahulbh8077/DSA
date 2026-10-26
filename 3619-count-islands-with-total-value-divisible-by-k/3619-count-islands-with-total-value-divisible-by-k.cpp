class Solution {
public:
    int m, n;
    
    long long dfs(vector<vector<int>>& grid, int i, int j) {
        // Out of bounds or water
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] <= 0)
            return 0;

        // Store value and mark visited
        long long sum = grid[i][j];
        grid[i][j] = 0;

        // Explore 4 directions
        sum += dfs(grid, i + 1, j);
        sum += dfs(grid, i - 1, j);
        sum += dfs(grid, i, j + 1);
        sum += dfs(grid, i, j - 1);

        return sum;
    }

    int countIslands(vector<vector<int>>& grid, int k) {
        m = grid.size();
        n = grid[0].size();

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] > 0) {
                    long long islandSum = dfs(grid, i, j);

                    if (islandSum % k == 0)
                        ans++;
                }
            }
        }

        return ans;
    }
};