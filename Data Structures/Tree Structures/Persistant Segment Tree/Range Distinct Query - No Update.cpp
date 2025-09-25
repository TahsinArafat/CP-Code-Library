#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ll long long
#define mid(L, R) ((L + R) >> 1)

struct PersistentSegmentTree {
    struct Node {
        int L = -1;
        int R = -1;
        int cnt = 0;
        Node() = default;
        Node(int left, int right, int count) : L(left), R(right), cnt(count) { }
    };

    vector<Node> tree;
    int gc = 0;
    int N = 0;

    PersistentSegmentTree(int n) : tree(), gc(0), N(n)
    {
        tree.reserve(max(1, n * 20));
    }

    int build(int L, int R)
    {
        tree.push_back(Node());
        int x = tree.size() - 1;
        if (L == R)
            return x;
        tree[x] = Node(build(L, mid(L, R)), build(mid(L, R) + 1, R), 0);
        return x;
    }

    int update(int L, int R, int root, int idx, int val)
    {
        if (L > idx || R < idx)
            return root;
        tree.push_back(Node());
        int x = tree.size() - 1;
        if (L == idx && R == idx) {
            tree[x] = Node(-1, -1, tree[root].cnt + val);
            return x;
        }
        tree[x] = Node(update(L, mid(L, R), tree[root].L, idx, val),
            update(mid(L, R) + 1, R, tree[root].R, idx, val),
            tree[root].cnt + val);
        return x;
    }

    int query(int L, int R, int root, int qe, int qr)
    {
        if (qr < L || qe > R)
            return 0;
        if (qe <= L && R <= qr)
            return tree[root].cnt;
        return query(L, mid(L, R), tree[root].L, qe, qr) + query(mid(L, R) + 1, R, tree[root].R, qe, qr);
    }
    void destroy()
    {
        tree.clear();
        tree.shrink_to_fit();
    }
};

void compressArray(vector<int>& A)
{
    vector<int> B = A;
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    for (int i = 1; i < (int)A.size(); ++i)
        A[i] = lower_bound(B.begin(), B.end(), A[i]) - B.begin() + 1;
    B.clear();
    B.shrink_to_fit();
}

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        int N, maxA = 0;
        cin >> N;
        vector<int> A(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
        }
        compressArray(A);
        for (int i = 1; i <= N; ++i)
            maxA = max(maxA, A[i]);
        PersistentSegmentTree pst(N);
        vector<int> G(maxA + 1, -1), root(N + 1);
        root[0] = pst.build(1, N);
        for (int i = 1; i <= N; ++i) {
            int p = root[i - 1];
            if (G[A[i]] != -1)
                p = pst.update(1, N, p, G[A[i]], -1);
            root[i] = pst.update(1, N, p, i, 1);
            G[A[i]] = i;
        }
        int M;
        cin >> M;
        while (M--) {
            int x, y;
            cin >> x >> y;
            printf("%d\n", pst.query(1, N, root[y], x, y));
        }
        pst.destroy();
        A.clear();
        A.shrink_to_fit();
    }
    return 0;
}
// https://www.spoj.com/problems/DQUERY/en/