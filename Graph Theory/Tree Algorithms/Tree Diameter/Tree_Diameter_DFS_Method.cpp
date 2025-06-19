#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

pair<ll, ll> farthestNode(ll node, ll par, vector<ll> tree[]) // pair<ll, ll> = {farthestNode, distance}
{
    pair<ll, ll> res = { node, 0 };
    for (auto& it : tree[node]) {
        if (it != par) {
            auto tmp = farthestNode(it, node, tree);
            tmp.second++;
            if (tmp.second > res.second) {
                res = tmp;
            }
        }
    }
    return res;
}

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<ll> tree[n + 1];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    auto x = farthestNode(1, -1, tree);
    auto y = farthestNode(x.first, -1, tree);
    cout << y.second << '\n';
    return 0;
}

// https://cses.fi/problemset/task/1131 Tree Diameter