
class Solution {
public:
    unordered_map<string, vector<int>> dp;

    vector<int> diffWaysToCompute(string expression) {

        // Return already calculated results
        if (dp.count(expression)) {
            return dp[expression];
        }

        vector<int> ans;

        for (int i = 0; i < expression.length(); i++) {

            char op = expression[i];

            // Check if current character is an operator
            if (op == '+' || op == '-' || op == '*') {

                string left = expression.substr(0, i);
                string right = expression.substr(i + 1);

                // Calculate all possible left results
                vector<int> leftResults = diffWaysToCompute(left);

                // Calculate all possible right results
                vector<int> rightResults = diffWaysToCompute(right);

                // Combine every possible pair of results
                for (int a : leftResults) {
                    for (int b : rightResults) {

                        if (op == '+') {
                            ans.push_back(a + b);
                        }
                        else if (op == '-') {
                            ans.push_back(a - b);
                        }
                        else {
                            ans.push_back(a * b);
                        }
                    }
                }
            }
        }

        // If no operator exists, expression is a number
        if (ans.empty()) {
            ans.push_back(stoi(expression));
        }

        return dp[expression] = ans;
    }
};
