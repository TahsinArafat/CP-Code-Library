#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll

struct LazySegmentTree {
    vector<int> tree, lazy;
    ll n;
    LazySegmentTree(vector<int>& a) { n = a.size(), tree.assign(4 * n + 1, 0), lazy.assign(4 * n + 1, 0), buildTree(a, 1, 0, n - 1); }
    LazySegmentTree(ll n) { this->n = n, tree.assign(4 * n + 1, 0), lazy.assign(4 * n + 1, 0); }
    void buildTree(vector<int>& a, ll index, ll s, ll e)
    {
        if (s > e)
            return;
        if (s == e) {
            tree[index] = a[s];
            return;
        }
        ll m = (s + e) >> 1;
        buildTree(a, index << 1, s, m), buildTree(a, (index << 1) | 1, m + 1, e);
        tree[index] = tree[index << 1] + tree[(index << 1) | 1];
    }
    void updateRange(ll rs, ll re, ll inc) { updateRange(1, 0, n - 1, rs, re, inc); }
    void updateRange(ll index, ll s, ll e, ll rs, ll re, ll inc)
    {
        if (lazy[index] != 0) {
            tree[index] += (e - s + 1) * lazy[index];
            if (s != e)
                lazy[index << 1] += lazy[index], lazy[(index << 1) | 1] += lazy[index];
            lazy[index] = 0;
        }

        if (s > e || s > re || e < rs)
            return;

        if (s >= rs && e <= re) {
            tree[index] += (e - s + 1) * inc;
            if (s != e)
                lazy[index << 1] += inc, lazy[(index << 1) | 1] += inc;
            return;
        }

        ll m = (s + e) >> 1;
        updateRange(index << 1, s, m, rs, re, inc), updateRange((index << 1) | 1, m + 1, e, rs, re, inc);
        tree[index] = tree[index << 1] + tree[(index << 1) | 1];
    }
    ll query(ll rs, ll re) { return query(1, 0, n - 1, rs, re); }
    ll query(ll index, ll s, ll e, ll rs, ll re)
    {
        if (lazy[index] != 0) {
            tree[index] += (e - s + 1) * lazy[index];
            if (s != e)
                lazy[index << 1] += lazy[index], lazy[(index << 1) | 1] += lazy[index];
        }
        lazy[index] = 0;
        if (s > e || s > re || e < rs)
            return 0;
        if (s >= rs && e <= re)
            return tree[index];
        ll m = (s + e) >> 1, left = query(index << 1, s, m, rs, re), right = query((index << 1) | 1, m + 1, e, rs, re);
        return left + right;
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> a = { 1, 3, 5, 7, 9, 11 };
    LazySegmentTree segTree(a);

    cout << segTree.query(3, 5) << endl;
    segTree.updateRange(2, 5, 10);
    cout << segTree.query(3, 5) << endl;
    cout << segTree.query(4, 4) << endl;
    segTree.updateRange(1, 4, 3);
    for (ll i = 0; i < 6; i++) {
        cout << segTree.query(i, i) << endl;
    }
    return 0;
}
