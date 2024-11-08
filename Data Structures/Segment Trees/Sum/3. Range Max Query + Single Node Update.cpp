struct SegmentTree {
    vector<int> tree;
    int n;

    SegmentTree(int size)
    {
        n = size;
        tree.resize(4 * n, 0);
    }

    void build(vector<int>& a)
    {
        buildTree(1, 0, n - 1, a);
    }

    void buildTree(int index, int s, int e, vector<int>& a)
    {
        if (s > e)
            return;
        if (s == e) {
            tree[index] = a[s];
            return;
        }
        int m = (s + e) / 2;
        buildTree(2 * index, s, m, a);
        buildTree(2 * index + 1, m + 1, e, a);
        tree[index] = max(tree[2 * index], tree[2 * index + 1]);
    }

    int query(int qs, int qe)
    {
        return queryTree(1, 0, n - 1, qs, qe);
    }

    int queryTree(int index, int s, int e, int qs, int qe)
    {
        if (qs > e || s > qe)
            return 0;
        if (s >= qs && e <= qe)
            return tree[index];
        int m = (s + e) / 2;
        int left_ans = queryTree(2 * index, s, m, qs, qe);
        int right_ans = queryTree(2 * index + 1, m + 1, e, qs, qe);
        return max(left_ans, right_ans);
    }

    void update(int pos, int val)
    {
        updateTree(1, 0, n - 1, pos, val);
    }

    void updateTree(int index, int s, int e, int pos, int val)
    {
        if (pos < s || pos > e)
            return;
        if (s == e) {
            tree[index] = val;
            return;
        }
        int m = (s + e) / 2;
        updateTree(2 * index, s, m, pos, val);
        updateTree(2 * index + 1, m + 1, e, pos, val);
        tree[index] = max(tree[2 * index], tree[2 * index + 1]);
    }
};
