#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
using ll = unsigned long long;

ll mul(ll x, ll y, ll n) {
    ll a = x % n;
    ll res = 0;
    while (y) {
        if (y & 1) {
            res += a;
            res %= n;
        }
        a <<= 1;
        a %= n;
        y >>= 1;
    }
    return res;
}


ll binpow(ll a, ll n, ll mod) {//a^n % mod
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = mul(res, a, mod);
            res %= mod;
        }
        a = mul(a, a, mod);
        n >>= 1;
    }
    return res;
}

pair<ll, ll> getS_D(ll n) {
    ll s = 0;
    while (((n & 1) == 0) && (n > 0)) {
        ++s;
        n >>= 1;
    }
    return {s, n};
}


bool oneCheck(ll n, ll s, ll d) {
    ll a = ((rand() % (n - 2)) + 2);
    auto a_d = binpow(a, d, n);
    if (a_d == 1 || a_d == n - 1) return true;
    for (ll i = 0; i < s; i++) {
        a_d = mul(a_d, a_d, n);
        if (a_d == n - 1) return true;
    }
    return false;
}

bool isPrime(ll n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    pair<ll, ll> pair = getS_D(n - 1);
    ll r = 5;
    for (ll i = 0; i < r; i++) {
        if (!oneCheck(n, pair.first, pair.second)) return false;
    }
    return true;
}

void solve() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll a;
        cin >> a;
        cout << (isPrime(a) ? "YES" : "NO") << "\n";
    }

}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
//    cout << ULLONG_MAX << endl;
//    cout << MAX;
    return 0;
}
