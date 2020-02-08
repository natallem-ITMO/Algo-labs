
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <climits>

using namespace std;
int MAX = 10000 * 1000;
struct edge {
    int a, b, w;
};

void fall() {
    vector<int> n;
    cout << n[10];
}

void solve() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> input_edges(n + 1, vector<pair<int, int>>());
    vector<edge> ed;
    vector<int> d(n + 1, 0);
    vector<int> p(n + 1, -1);
    vector<int> loops;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            if (a == 100000) continue;
            if (i == j && a < 0) {
                loops.push_back(i);

               // continue;
            }
            ed.push_back({i, j, a});
        }
    }
    for (int i = 0; i < n*10; i++) {
        for (auto e : ed) {
            if (d[e.b] > d[e.a] + e.w) {
                d[e.b] = d[e.a] + e.w;
                p[e.b] = e.a;
            }
        }
    }
    vector<int> ans;
    for (auto e : ed) {
        int v = e.b;
        int u = e.a;
        if (d[v] > d[u] + e.w) {

            for (int i = 0; i < n; i++) {
                v = p[v];
            }

            u = v;
            v = p[v];
            ans.push_back(u);
            while (u != v) {
                ans.push_back(v);
                v = p[v];
            }
        }
    }
    if (ans.empty()) {
        cout << "NO";
      //  fall();
    }
    else {
        cout << "YES\n" << ans.size() << "\n";
        for (int i : ans) {
            cout << i << " ";
        }
    };
}

int main() {
    solve();
}