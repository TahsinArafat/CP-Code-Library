#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long

struct UnionFind {
    vector<int> p, rank, setSize;
    int numSets;
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i)
            p[i] = i;
        rank.assign(N, 0);
        setSize.assign(N, 1);
        numSets = N;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
    void unionSet(int i, int j)
    {
        if (isSameSet(i, j))
            return;
        int x = findSet(i), y = findSet(j);
        if (rank[x] > rank[y])
            swap(x, y);
        p[x] = y;
        if (rank[x] == rank[y])
            ++rank[y];
        setSize[y] += setSize[x];
        --numSets;
    }
};

int32_t main()
{
    // UnionFind UF(5); // create 5 disjoint sets
    // printf("%d\n", UF.numDisjointSets()); // 5
    // UF.unionSet(0, 1);
    // printf("%d\n", UF.numDisjointSets()); // 4
    // UF.unionSet(2, 3);
    // printf("%d\n", UF.numDisjointSets()); // 3
    // UF.unionSet(4, 3);
    // printf("%d\n", UF.numDisjointSets()); // 2
    // printf("isSameSet(0, 3) = %d\n", UF.isSameSet(0, 3)); // 0 (false)
    // printf("isSameSet(4, 3) = %d\n", UF.isSameSet(4, 3)); // 1 (true)
    // for (int i = 0; i < 5; ++i) // 1 for {0, 1} and 3 for {2, 3, 4}
    //     printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n",
    //         i, UF.findSet(i), i, UF.sizeOfSet(i));
    // UF.unionSet(0, 3);
    // printf("%d\n", UF.numDisjointSets()); // 1
    // for (int i = 0; i < 5; ++i) // 3 for {0, 1, 2, 3, 4}
    //     printf("findSet(%d) = %d, sizeOfSet(%d) = %d\n",
    //         i, UF.findSet(i), i, UF.sizeOfSet(i));
    return 0;
}
