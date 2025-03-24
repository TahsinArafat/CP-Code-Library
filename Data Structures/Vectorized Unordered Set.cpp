// Vectorized Unordered Set
// Supported range of elements: [0, N]
// Space Complexity: O(N)
// Time Complexity: for inserting/erasing/checking/accessing_last_inserted_valid_element O(1) on average, for building O(N)

// Insertion is once at a time, (only can be inserted if not present now)
// I am gonna update multiple time insertion in future

struct node {
    node *l, *r;
    node() { l = r = nullptr; }
};
struct vcUset {
    vector<node> store;
    ll ans = -1;
    vcUset(ll n) { store = vector<node>(n + 1); }
    void erase(ll x)
    {
        if (store[x].l != nullptr)
            store[x].l->r = store[x].r;
        if (store[x].r != nullptr)
            store[x].r->l = store[x].l;
        if (ans == x) {
            ans = -1;
            if (store[x].l != nullptr)
                ans = store[x].l - &store[0];
        }
        store[x].l = store[x].r = nullptr;
    }
    void insert(ll x)
    {
        if (ans != -1)
            store[ans].r = &store[x], store[x].l = &store[ans];
        ans = x;
    }
    bool count(ll x) { return store[x].l != nullptr || store[x].r != nullptr || ans == x; }
};
