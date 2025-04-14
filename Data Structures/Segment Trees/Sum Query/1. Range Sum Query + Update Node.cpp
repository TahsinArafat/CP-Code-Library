#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct SumSeg {
    vector<ll> tree;
    ll n = 0;
    SumSeg(vector<ll>& a) { n = a.size(); tree.assign(4 * n + 1, 0); buildTree(a, 1, 0, n - 1); }
    SumSeg(ll n) { tree.assign(4 * n + 1, 0); }
    void buildTree(vector<ll>& a, ll index, ll s, ll e) {
        if (s > e) return;
        if (s == e) { tree[index] = a[s]; return; }
        ll m = (s + e) >> 1;
        buildTree(a, index << 1, s, m), buildTree(a, (index << 1) + 1, m + 1, e);
        tree[index] = tree[index << 1] + tree[(index << 1) + 1];
    }
    ll query(ll l, ll r) { return query(1, 0, n - 1, l, r); }
    ll query(ll pos) { return query(pos, pos);}
    ll query(ll index, ll s, ll e, ll l, ll r) {
        if (l > e || s > r) return 0;
        if (s >= l && e <= r) return tree[index];
        ll m = (s + e) >> 1;
        return query(index << 1, s, m, l, r) + query((index << 1) + 1, m + 1, e, l, r);
    }
    void updateNode(ll pos, ll val) { updateNode(1, 0, n - 1, pos, val); }
    void updateNode(ll index, ll s, ll e, ll pos, ll val) {
        if (pos < s || pos > e) return;
        if (s == e) { tree[index] = val; return; }
        ll m = (s + e) >> 1;
        updateNode(index << 1, s, m, pos, val), updateNode((index << 1) + 1, m + 1, e, pos, val);
        tree[index] = tree[index << 1] + tree[(index << 1) + 1];
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    vector<ll> a = { 1, 3, 2, -2, 4, 5 };
    SumSeg sTree(a);

	// Demo Operations
	cout << sTree.query(0, 5) << "\n";
    cout << sTree.query(2, 5) << "\n";
	sTree.updateNode(1, -11);
	cout << sTree.query(0, 0) << "\n";
	cout << sTree.query(4) << "\n";
    return 0;
}
