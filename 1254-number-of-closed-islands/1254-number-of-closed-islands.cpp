class Solution {
public:
    bool dfs(vector<vector<int>>& grid, int r, int c) {
        int m = grid.size();
        int n = grid[0].size();

        // Went outside the grid
        // This means the island touches the boundary.
        if (r < 0 || r >= m || c < 0 || c >= n) {
            return false;
        }

        // Water
        if (grid[r][c] == 1) {
            return true;
        }

        // Mark this land cell as visited
        grid[r][c] = 1;

        bool up = dfs(grid, r - 1, c);
        bool down = dfs(grid, r + 1, c);
        bool left = dfs(grid, r, c - 1);
        bool right = dfs(grid, r, c + 1);

        // Island is closed only if ALL four directions
        // remain inside the grid.
        return up && down && left && right;
    }

    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 0) {
                    if (dfs(grid, i, j)) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};