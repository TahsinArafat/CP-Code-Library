using ll = long long;
struct P {
    ll x, y;
};

__int128 cross128(const P& a, const P& b, const P& c)
{   // cross of (b-a) x (c-a)
    __int128 ux = (__int128)b.x - a.x;
    __int128 uy = (__int128)b.y - a.y;
    __int128 vx = (__int128)c.x - a.x;
    __int128 vy = (__int128)c.y - a.y;
    return ux * vy - uy * vx;
}

bool cmpXY(const P& a, const P& b)
{
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

vector<P> convexHull(vector<P> pts)
{
    sort(pts.begin(), pts.end(), cmpXY);
    int n = (int)pts.size();
    if (n <= 1)
        return pts;
    vector<P> lower, upper;
    for (int i = 0; i < n; ++i) {
        while (lower.size() >= 2 && cross128(lower[lower.size() - 2], lower[lower.size() - 1], pts[i]) <= 0)
            lower.pop_back();
        lower.push_back(pts[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        while (upper.size() >= 2 && cross128(upper[upper.size() - 2], upper[upper.size() - 1], pts[i]) <= 0)
            upper.pop_back();
        upper.push_back(pts[i]);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}