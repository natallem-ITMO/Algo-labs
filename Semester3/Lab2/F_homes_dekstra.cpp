#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <climits>
#include <set>
#include <list>
#include <unordered_map>

using namespace std;
using ll =  long long int;
int n, a, b, c;
vector<ll> d;
unordered_map<int, vector<pair<int, ll>>> edges;


using namespace std;
ll MAX = LONG_LONG_MAX;


void deikstra(int start) {
    for (int i = 1; i <= n; i++) d[i] = MAX;
    d[start] = 0;
    set<pair<ll, int>> B;
    B.insert({0, start});
    while (!B.empty()) {
        auto minPairPtr = B.begin();
        int min_v = minPairPtr->second;
        ll min_w = minPairPtr->first;
        B.erase(minPairPtr);
        if (min_w > d[min_v]) continue;//<-----------------------------------------------------------------------------
        for (auto &pair : edges[min_v]) {
            int u = pair.first;
            ll w = pair.second;
            if (d[u] > d[min_v] + w) {
                B.erase({u, d[u]});
                d[u] = d[min_v] + w;
                B.insert({d[u], u});
            }
        }
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
    int m;
    cin >> n >> m;
    d.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    cin >> a >> b >> c;
    deikstra(a);
    ll a_b = d[b];
    ll a_c = d[c];
    deikstra(b);
    ll b_c = d[c];
    if (a_b == MAX || a_c == MAX || b_c == MAX) {
        cout << -1;
        return 0;
    }
    ll path = min(a_b + b_c, min(b_c + a_c, a_b + a_c));
    cout << path;
}