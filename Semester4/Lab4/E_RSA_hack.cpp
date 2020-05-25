#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <queue>

using namespace std;

void fall() {
    vector<long long> f;
    cout << f[123];
}

auto getPrimes(long long MAX) {
    vector<bool> sieve(MAX + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= MAX; i++) {
        if (sieve[i] == 0) {
            for (long long j = 2;; j++) {
                long long s = j * i;
                if (s > MAX) break;
                sieve[s] = true;
            }
            primes.push_back(i);
        }
    }
    return primes;
}

auto find_p_q(long long n) {
    for (long long i = 2; i < sqrt(n)+1; i++){
        if (n % i == 0){
            return make_pair(i,  n / i);
        }
    }
    fall();
}

long long gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

long long getInverseElementToA(long long a, long long m) {
    long long x, y;
    long long g = gcd(a, m, x, y);
    if (g != 1) {
        fall();
        cout << "no solution";
    } else {
        x = (x % m + m) % m;
        return x;
    }
}

long long mul(long long x, long long y, long long n) {
    long long a = x % n;
    long long res = 0;
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


long long binpow(long long a, long long n, long long mod) {//a^n % mod
    a %= mod;
    long long res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n >>= 1;
    }
    return res;
}

long long solution(long long n, long long e, long long C) {
    auto[p, q] = find_p_q(n);
    long long phi_n_ = (p - 1) * (q - 1);
    if (phi_n_ == 0) fall();
    long long d = getInverseElementToA(e, phi_n_);
    return binpow(C, d, n);

}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n, e, C;
    cin >> n >> e >> C;
    cout << solution(n, e, C);


    return 0;
}
