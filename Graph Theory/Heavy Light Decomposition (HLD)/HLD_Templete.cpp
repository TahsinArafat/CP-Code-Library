#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

struct FenwickTree {
    vector<int> bit;
    int n;
    FenwickTree(int n)
    {
        this->n = n;
        bit.assign(n, 0);
    }
    int sum(int r)
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta)
    {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

struct HLD {
    int n, cur_pos = 0;
    vector<int> arr, parent, size, depth, heavy, head, pos;
    vector<vector<int>> adj;
    FenwickTree segtree;
    HLD(int n)
        : n(n)
        , arr(n + 1)
        , parent(n + 1)
        , size(n + 1)
        , depth(n + 1)
        , heavy(n + 1, 0)
        , head(n + 1)
        , pos(n + 1)
        , adj(n + 1)
        , segtree(FenwickTree(n + 1))
    {
    }
    void add_edge(int u, int v)
    {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void dfs(int u, int p)
    {
        parent[u] = p;
        size[u] = 1;
        int max_sz = 0;
        for (int v : adj[u]) {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            size[u] += size[v];
            if (size[v] > max_sz) {
                max_sz = size[v], heavy[u] = v;
            }
        }
    }
    void decompose(int u, int h)
    {
        head[u] = h;
        pos[u] = cur_pos++;
        segtree.add(pos[u], arr[u]); // Update Fenwick tree with the value of arr[u]
        if (heavy[u])
            decompose(heavy[u], h);
        for (int v : adj[u])
            if (v != parent[u] && v != heavy[u])
                decompose(v, v);
    }
    int query(int u, int v)
    { // Range Sum Query
        int res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            res += segtree.sum(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        res += segtree.sum(pos[u], pos[v]);
        return res;
    }
    void addVal(int idx, int delta)
    {
        segtree.add(pos[idx], delta);
        arr[idx] += delta;
    }
    void editVal(int idx, int value)
    {
        segtree.add(pos[idx], value - arr[idx]);
        arr[idx] = value;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    for (int i = 1; i <= n; i++)
        cin >> hld.arr[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.dfs(1, -1), hld.decompose(1, 1);
    while (q--) {
        ll qtype;
        cin >> qtype;
        if (qtype == 1) {
            ll posi, val;
            cin >> posi >> val;
            hld.editVal(posi, val);
        } else {
            ll u;
            cin >> u;
            cout << hld.query(1, u) << "\n";
        }
    }
}

// https://cses.fi/problemset/task/1138/