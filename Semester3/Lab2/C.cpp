
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


const int INF = 1000000000;
struct edge {
    int a, b, w;
};

void fall() {
    vector<int> b;
    cout << b[10];
}

void solve() {
    //fall();

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<edge> e;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            if (a == 100000) continue;
            e.push_back(edge{i, j, a});
        }
    }

    vector<int> d(n + 1,0);
    vector<int> p(n + 1, -1);
    int x=-1;
    int m = e.size();
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (int j = 0; j < m; ++j)
            if (d[e[j].b] > d[e[j].a] + e[j].w) {
                d[e[j].b] = d[e[j].a] + e[j].w;
                p[e[j].b] = e[j].a;
                x = e[j].b;
            }
    }

    if (x == -1) {
        cout << "NO\n";
        //fall();
    } else {
        int y = x;
        for (int i = 0; i < n; ++i)
            y = p[y];

        vector<int> path;

        int cur = y;
        while (cur != y || path.empty())
        {
            path.push_back(cur);
            cur = p[cur];
        }
        reverse(path.begin(), path.end());

        cout << "YES\n" << path.size() << "\n";
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] << ' ';
    }

}

int main() {
    solve();
}

