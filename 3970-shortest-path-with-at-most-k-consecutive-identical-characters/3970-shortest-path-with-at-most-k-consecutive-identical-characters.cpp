class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        vector<vector<pair<int, int>>> graph(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            graph[u].push_back({v, w});
        }

        // dist[node][consecutive_count]
        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, LLONG_MAX)
        );

        // {distance, node, consecutive_count}
        using State = tuple<long long, int, int>;

        priority_queue<State, vector<State>, greater<State>> pq;

        // Starting node has a consecutive count of 1
        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [d, u, cnt] = pq.top();
            pq.pop();

            if (d != dist[u][cnt])
                continue;

            // Reached destination
            if (u == n - 1)
                return d;

            for (auto &[v, w] : graph[u]) {

                int newCnt;

                if (labels[u] == labels[v])
                    newCnt = cnt + 1;
                else
                    newCnt = 1;

                // Cannot have more than k identical characters
                if (newCnt > k)
                    continue;

                long long newDist = d + w;

                if (newDist < dist[v][newCnt]) {
                    dist[v][newCnt] = newDist;

                    pq.push({
                        newDist,
                        v,
                        newCnt
                    });
                }
            }
        }

        return -1;
    }
};