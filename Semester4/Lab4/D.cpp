#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;
using ull = unsigned long long;

long long gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        if (x==0){
            re
        }
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g != 0)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 *= -1;
    if (b < 0) y0 *= -1;
    return true;
}


pair<long long, long long> solve(long long a, long long b, long long n, long long m) {
    long long x0, y0, g;

    find_any_solution(n, -m, b - a, x0, y0, g);

    return {b + y0 * m, n * m};

}

long long solution(long long a, long long b, long long n, long long m) {
    auto[r, t] = solve(a, b, n, m);
    long long tt = r / t;
    if (tt < 0 || r < 0) tt += 1;
    r += t * tt;
    t = abs(t);
    while (r < 0) {
        r += t;
    }
    while (r >= 0) {
        r -= t;
    }
    return r + t;
}
int  main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long a, b, n, m;
    cin >> a >> b >> n >> m;
    if (a > b) {
        swap(a, b);
        swap(n, m);
    }
//    auto t = solve(a,b,n, m);
//    cout << t.first << " " << t.second<<"\n";
    cout << solution(a, b, n, m);


    return 0;
}
