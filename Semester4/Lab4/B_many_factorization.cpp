#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;
using ull = unsigned long long;
int MAX = 1000000;

auto getFactorization() {
    vector<int> primes;
    vector<pair<int,int>> p(MAX + 1, {0,1});
    for (int i = 2; i <= MAX; i++) {
        if (p[i].first == 0) {
            p[i].first = i;
            primes.push_back(i);
        }
        int pi = p[i].first;
        for (auto t : primes) {
            if (t > pi) break;
            if (i*t > MAX) break;
            p[i*t].first = t;
            p[i*t].second = i;
        }
    }
    return p;
}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    auto fact = getFactorization();


    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;

        auto p = fact[a];
        cout << p.first  << " ";

        while (p.second != 1){
            p = fact[p.second];
            cout << p.first << " ";
        }
        cout << "\n";
    }


    return 0;
}
