struct HLD {
    int n;
    vector<vector<int>> E;
    vector<int> p, h, head, L, R;
    HLD(const vector<vector<int>>& E, int root) : n((int)size(E)), E(E), p(n, -1), h(n), head(n), L(n), R(n) {
        dfs_sz(root);
        head[root] = root;
        dfs_hld(root);
    }
    int dfs_sz(int u) {
        int sz = 1, mx = 0;
        for (auto& v : E[u]) {
            if (v == p[u]) continue;
            p[v] = u, h[v] = h[u] + 1;
            int x = dfs_sz(v);
            sz += x;
            if (x > mx) {
                mx = x;
                swap(v, E[u][0]);
            }
        }
        return sz;
    }
    int timer = 0;
    void dfs_hld(int u) {
        L[u] = timer++;
        for (auto v : E[u]) {
            if (v == p[u]) continue;
            head[v] = (v == E[u][0] ? head[u] : v);
            dfs_hld(v);
        }
        R[u] = timer - 1;
    }
    // boolean is true if path should be 'reversed' (for uncommutative operations)
    vector<tuple<bool, int, int>> get_path(int u, int v) const {
        vector<tuple<bool, int, int>> left, right;
        while (head[u] != head[v]) {
            if (h[head[u]] > h[head[v]]) {
                left.emplace_back(true, L[head[u]], L[u]);
                u = p[head[u]];
            }
            else {
                right.emplace_back(false, L[head[v]], L[v]);
                v = p[head[v]];
            }
        }
        h[u] > h[v] ? left.emplace_back(true, L[v], L[u]) : right.emplace_back(false, L[u], L[v]);
        left.insert(end(left), rbegin(right), rend(right));
        return left;
    }
    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (h[head[u]] < h[head[v]]) swap(u, v);
            u = p[head[u]];
        }
        return h[u] < h[v] ? u : v;
    }
};
