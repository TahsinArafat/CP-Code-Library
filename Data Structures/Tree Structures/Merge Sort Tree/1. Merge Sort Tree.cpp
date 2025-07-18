#include <bits/stdc++.h>
using namespace std;
#define int long long

struct MergeSortTree {
    vector<vector<int>> tree;
    vector<int> arr;
    int n;
    MergeSortTree(vector<int>& a)
    {
        arr = a, n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }
    void build(int node, int l, int r)
    {
        if (l == r) {
            tree[node].push_back(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid), build(node * 2 + 1, mid + 1, r);
        tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
        merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
    }
    int query(int node, int l, int r, int ql, int qr, int k)
    {
        if (l > qr || r < ql)
            return 0;
        if (l >= ql && r <= qr) {
            int hi = tree[node].size() - 1, lo = 0, ind = -1;
            // while (hi >= lo) { } // Modify your function here
            return ind;
        }
        int mid = (l + r) / 2;
        return query(node * 2, l, mid, ql, qr, k) + query(node * 2 + 1, mid + 1, r, ql, qr, k);
    }
};

int32_t main()
{
    return 0;
}
