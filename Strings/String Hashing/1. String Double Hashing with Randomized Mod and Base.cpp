#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define xx first
#define yy second
mt19937 rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count());

ll modpow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return (res + mod) % mod;
}
bool isPrime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}
struct Hash {
    string s;
    int n = 0;
    ll mod1 = 127657753, mod2 = 987654319;
    ll p1 = 31, p2 = 37;
    ll invp1 = modpow(p1, mod1 - 2, mod1), invp2 = modpow(p2, mod2 - 2, mod2);
    vector<pair<ll, ll>> sHash, pPow, invpPow;
    void setVal(string& S) { // Set the string
        s = S, n = S.size();
    }
    void randomize() { // Randomize the mod and base
        p1 = rnd() % 100 + 31, p2 = rnd() % 100 + 37;
        while (!isPrime(p1)) p1++;
        while (!isPrime(p2) || p1 == p2) p2++;
        invp1 = modpow(p1, mod1 - 2, mod1), invp2 = modpow(p2, mod2 - 2, mod2);
        mod1 = rnd() % 100000000 + 900000000, mod2 = rnd() % 100000000 + 900000000;
        while (!isPrime(mod1)) mod1++;        
        while (!isPrime(mod2) || mod1 == mod2) mod2++;
    }
    void genP() { // Generate powers of p and invp for faster queries
        pPow.resize(n + 1, {1, 1});
        invpPow.resize(n + 1, {1, 1});
        for (int i = 1; i <= n; i++) {
            pPow[i].xx = pPow[i - 1].xx * p1 % mod1;
            pPow[i].yy = pPow[i - 1].yy * p2 % mod2;
            invpPow[i].xx = invpPow[i - 1].xx * invp1 % mod1;
            invpPow[i].yy = invpPow[i - 1].yy * invp2 % mod2;
        }
    }
    void genHash() { // 0-indexed
        sHash.resize(n + 1, {0, 0});
        for (int i = 0; i < n; i++) {
            sHash[i + 1].xx = (sHash[i].xx + (s[i] - 'a' + 1) * pPow[i].xx) % mod1;
            sHash[i + 1].yy = (sHash[i].yy + (s[i] - 'a' + 1) * pPow[i].yy) % mod2;
        }
    }
    pair<ll, ll> getHash(int l, int r) { // 0-indexed
        ll h1 = (sHash[r + 1].xx - sHash[l].xx + mod1) % mod1 * invpPow[l].xx % mod1;
        ll h2 = (sHash[r + 1].yy - sHash[l].yy + mod2) % mod2 * invpPow[l].yy % mod2;
        return {h1, h2};
    }
    pair<ll, ll> getHash() { // Get the hash of the whole string
        return getHash(0, n - 1);
    }
    void doAll(string& S) {
        setVal(S), randomize(), genP(), genHash();
    }
};

int32_t main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string s;
    cin >> s;
    Hash h; // Create a hash object
    // h.setVal(s); // Set the string
    // h.randomize(); // Randomize the mod and base
    // h.genP(); // Generate the powers
    // h.genHash(); // Generate the hash
    h.doAll(s);
    cout << h.getHash().xx << ' ' << h.getHash().yy << '\n'; // Get the hash of the whole string
    return 0;    
}
