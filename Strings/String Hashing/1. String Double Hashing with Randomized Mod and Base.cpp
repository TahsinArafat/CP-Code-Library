#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define xx first
#define yy second
mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

ll ModPow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return (res + mod) % mod;
}
bool isPrime(ll n) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (ll i = 5; i * i <= n; i += 6) if (n % i == 0 || n % (i + 2) == 0) return 0;
    return 1;
}
ll mod1 = 127657753, mod2 = 987654319, p1 = 31, p2 = 37;
ll invp1 = ModPow(p1, mod1 - 2, mod1), invp2 = ModPow(p2, mod2 - 2, mod2);
vector<pair<ll, ll>> pPow(1, {1, 1}), iPow(1, {1, 1});
void randomize() {
    mod1 = (rnd() % 100000000 + 900000000) | 1, mod2 = (rnd() % 100000000 + 900000000) | 1;
    while (!isPrime(mod1)) mod1 += 2;        
    while (!isPrime(mod2) || mod1 == mod2) mod2 += 2;
    p1 = (rnd() % 100 + 31) | 1, p2 = (rnd() % 100 + 37) | 1;
    while (!isPrime(p1)) p1 += 2;
    while (!isPrime(p2) || p1 == p2) p2 += 2;
    invp1 = ModPow(p1, mod1 - 2, mod1), invp2 = ModPow(p2, mod2 - 2, mod2);
}
void genP(ll n) {
    while (pPow.size() <= n) {
        pPow.push_back({pPow.back().xx * p1 % mod1, pPow.back().yy * p2 % mod2});
        iPow.push_back({iPow.back().xx * invp1 % mod1, iPow.back().yy * invp2 % mod2});
    }
}
struct Hash {
    string s;
    int n = 0;
    vector<pair<ll, ll>> sHash;
    void genHash() {
        sHash.resize(n + 1, {0, 0}); // 0-indexed
        for (int i = 0; i < n; i++) {
            sHash[i + 1].xx = (sHash[i].xx + (s[i] - 'a' + 1) * pPow[i].xx) % mod1;
            sHash[i + 1].yy = (sHash[i].yy + (s[i] - 'a' + 1) * pPow[i].yy) % mod2;
        }
    }
    pair<ll, ll> getHash(int l, int r) {
        ll h1 = (sHash[r + 1].xx - sHash[l].xx + mod1) % mod1 * iPow[l].xx % mod1;
        ll h2 = (sHash[r + 1].yy - sHash[l].yy + mod2) % mod2 * iPow[l].yy % mod2;
        return {h1, h2}; // 0-indexed
    }
    pair<ll, ll> getHash() {
        return getHash(0, n - 1); // Get the hash of the whole string
    }
    Hash(string& S) {
        s = S, n = S.size();
        genP(n), genHash();
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    randomize(); // Randomize the mod and base
    string s;
    cin >> s;
    Hash h(s); // Create a hash object
    // cout << h.getHash().xx << ' ' << h.getHash().yy << '\n';
    return 0;    
}
