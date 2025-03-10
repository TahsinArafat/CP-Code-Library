// https : // www.spoj.com/problems/DQUERY/

#include <bits/stdc++.h>
using namespace std;
#define int long long
int BLOCK_SIZE;

struct Query {
    int L, R, idx;
};

bool cmp(const Query& a, const Query& b)
{
    int block_a = a.L / BLOCK_SIZE, block_b = b.L / BLOCK_SIZE;
    if (block_a != block_b)
        return block_a < block_b;
    return (block_a & 1) ? (a.R > b.R) : (a.R < b.R);
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> q;
    BLOCK_SIZE = static_cast<int>(sqrt(n));
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int L, R;
        cin >> L >> R;
        queries[i] = { --L, --R, i }; // 0-based indexing
    }
    sort(queries.begin(), queries.end(), cmp);

    long long ans1 = 0;
    vector<long long> freq(1000001, 0), ans(q);
    int curL = 0, curR = -1;

    auto add = [&](int idx) {
        int val = arr[idx];
        ans1 += (++freq[val] == 1);
    };
    auto remove = [&](int idx) {
        int val = arr[idx];
        ans1 -= (freq[val]-- == 1);
    };

    for (auto& qr : queries) {
        while (curR < qr.R)
            add(++curR);
        while (curR > qr.R)
            remove(curR--);
        while (curL < qr.L)
            remove(curL++);
        while (curL > qr.L)
            add(--curL);
        ans[qr.idx] = ans1;
    }

    for (auto& x : ans)
        cout << x << "\n";
    return 0;
}
