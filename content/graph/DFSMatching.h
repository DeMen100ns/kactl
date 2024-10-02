/**
 * Author: DeMen100ns
 * Date: 2024
 * Description: DeMen-Kuhn (Kuhn with Russian optimize)
 * Time: O(VE) but very fast in practice
 */

struct BipartiteMatching {
    int n;
    vector<vector<int>> adj;

    BipartiteMatching(int n) : n(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<int, 2>> getMCBM() {
        vector<int> match(n, -1);
        vector<int> vis(n, -1);
        int ite = 0;
        function<bool(int)> dfs = [&](int u) {
            if (vis[u] == ite) return false;
            vis[u] = ite;
            for (int v : adj[u]) {
                if (match[v] == -1 || dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
            return false;
        };
        for (bool run = true; run; ) {
            run = false;
            for (int u = 0; u < n; u++) {
                if (match[u] == -1) {
                    run |= dfs(u);
                }
            }
            ite++;
        }
        vector<array<int, 2>> res;
        for (int u = 0; u < n; u++) {
            if (match[u] != -1 && match[u] > u) {
                res.push_back({ u, match[u] });
            }
        }
        return res;
    }
};
