class Solution {
public:
    int totalNQueens(int n) {
        int ans = 0;

        vector<bool> col(n, false);
        vector<bool> diag1(2 * n, false);
        vector<bool> diag2(2 * n, false);

        solve(0, n, col, diag1, diag2, ans);

        return ans;
    }

private:
    void solve(int row, int n,
               vector<bool>& col,
               vector<bool>& diag1,
               vector<bool>& diag2,
               int& ans) {

        // All n queens have been placed
        if (row == n) {
            ans++;
            return;
        }

        for (int c = 0; c < n; c++) {

            // Check column and both diagonals
            if (col[c] || diag1[row + c] || diag2[row - c + n])
                continue;

            // Place queen
            col[c] = true;
            diag1[row + c] = true;
            diag2[row - c + n] = true;

            // Move to next row
            solve(row + 1, n, col, diag1, diag2, ans);

            // Backtrack
            col[c] = false;
            diag1[row + c] = false;
            diag2[row - c + n] = false;
        }
    }
};