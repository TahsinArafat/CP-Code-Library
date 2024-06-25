/*
Given arr[] = {a, b, c, d, ...} and an integer N, the task is to check if N can be represented as a linear combination of the array elements.
For example, N = a*x + b*y + c*z + … where x, y, z, … are integers.
*/
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define ll long long

bool isRepresentable(const vector<ll>& arr, ll N) {
    ll gcdArr = 0;
    for (auto& it : arr) {
        gcdArr = __gcd(gcdArr, it);
        if (gcdArr == 1) {
            return true;
        }
    }
    return N % gcdArr == 0;
}

int32_t main() {
    vector<ll> arr = {a, b, c, ...};
    ll N = ...;
    if (isRepresentable(arr, N)) {
        cout << N << " can be represented as a linear combination of the array elements." << "\n";
    } else {
        cout << N << " cannot be represented as a linear combination of the array elements." << "\n";
    }
    return 0;
}
