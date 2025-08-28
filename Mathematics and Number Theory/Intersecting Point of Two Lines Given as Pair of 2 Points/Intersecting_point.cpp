// Given
pair<ll, ll> a1, a2, b1, b2; // Line a1 to a2, and b1 to b2
// Find their intersecting point

auto cross = [](pair<ll, ll> a, pair<ll, ll> b) -> __int128 {
    return (__int128)a.first * b.second - (__int128)a.second * b.first;
};

pair<ll, ll> da = { a2.first - a1.first, a2.second - a1.second };
pair<ll, ll> db = { b2.first - b1.first, b2.second - b1.second };
pair<ll, ll> dc = { b1.first - a1.first, b1.second - a1.second };

__int128 denom = cross(da, db);
if (denom == 0) {
    // cout << "! 0 0" << endl;
    // No Intersection
} else {
    __int128 t_num = cross(dc, db); // parameter on line a
    __int128 u_num = cross(dc, da); // parameter on line b (if needed)
    // For segment intersection ensure 0 <= t_num <= denom (sign aware) and same for u.
    long double t = (long double)t_num / (long double)denom;
    long double x = a1.first + da.first * t;
    long double y = a1.second + da.second * t;
    cout << "! " << llround(x) << " " << llround(y) << endl;
}