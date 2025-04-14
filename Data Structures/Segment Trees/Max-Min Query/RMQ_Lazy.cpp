#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    vector<int> tree, lazy;
    int n;

    SegmentTree(vector<int>& a) {
        n = a.size();
        tree.resize(4 * n + 1);
        lazy.resize(4 * n + 1, 0);
        buildTree(a, 1, 0, n - 1);
    }

    void buildTree(vector<int>& a, int idx, int s, int e) {
        if (s > e) return;
        if (s == e) {
            tree[idx] = a[s];
            return;
        }
        int m = (s + e) >> 1;
        buildTree(a, idx << 1, s, m);
        buildTree(a, (idx << 1) | 1, m + 1, e);
        tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
    }

    void updateNode(int idx, int s, int e, int pos, int val) {
        if (pos < s || pos > e) return;
        if (s == e) {
            tree[idx] = val;
            return;
        }
        int m = (s + e) >> 1;
        updateNode(idx << 1, s, m, pos, val);
        updateNode((idx << 1) | 1, m + 1, e, pos, val);
        tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
    }

    void updateRange(int idx, int s, int e, int rs, int re, int inc) {
        if (lazy[idx] != 0) {
            tree[idx] += lazy[idx];
            if (s != e) {
                lazy[idx << 1] += lazy[idx];
                lazy[(idx << 1) | 1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (s > e || s > re || e < rs) return;
        if (s >= rs && e <= re) {
            tree[idx] += inc;
            if (s != e) {
                lazy[idx << 1] += inc;
                lazy[(idx << 1) | 1] += inc;
            }
            return;
        }
        int m = (s + e) >> 1;
        updateRange(idx << 1, s, m, rs, re, inc);
        updateRange((idx << 1) | 1, m + 1, e, rs, re, inc);
        tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
    }

    int query(int idx, int s, int e, int rs, int re) {
        if (lazy[idx] != 0) {
            tree[idx] += lazy[idx];
            if (s != e) {
                lazy[idx << 1] += lazy[idx];
                lazy[(idx << 1) | 1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (s > e || s > re || e < rs) return INT_MAX;
        if (s >= rs && e <= re) return tree[idx];
        int m = (s + e) >> 1;
        int left = query(idx << 1, s, m, rs, re);
        int right = query((idx << 1) | 1, m + 1, e, rs, re);
        return min(left, right);
    }

    void updateRange(int rs, int re, int inc) {
        updateRange(1, 0, n - 1, rs, re, inc);
    }

    int query(int rs, int re) {
        return query(1, 0, n - 1, rs, re);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> a = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(a);

    segTree.updateRange(2, 5, 10);
    segTree.updateRange(1, 4, 3);
    cout << segTree.query(2, 5) << endl;

    segTree.updateRange(3, 4, -12);
    cout << segTree.query(2, 5) << endl;

    return 0;
}
