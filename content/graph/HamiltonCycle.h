/**
 * Author: Unknown
 * Description: Find Hamilton cycle in Undirected Graph
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
bool findHamiltonian(int n, vector<vector<int>> adj, vector<int> &solution) {
    int ite = 100;
    while (ite--) {
        vector<int> deg(n);
        for (int i = 0; i < n; i++) {
            shuffle(adj[i].begin(), adj[i].end(), rng);
            deg[i] = adj[i].size();
        }
        deg[0] = 1e9;
        int u = 0;
        vector<int> ans = { u };
        for (int i = 1; i < n; i++) {
            int v = u;
            for (int w : adj[u]) {
                if (deg[w] < deg[v]) v = w;
            }
            if (deg[v] > 1e8) break;
            ans.push_back(v);
            u = v;
            for (int w : adj[u]) deg[w]--;
            deg[u] = 1e9;
        }
        if ((int)ans.size() == n) {
            bool ok = false;
            for (int v : adj[ans.back()]) if (v == ans.front()) ok = true;
            if (!ok) continue;
            solution = ans;
            return true;
        }
    }
    return false;
}
