#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

struct edge {
    int from, to, f, c;
    int inv;

    edge(int from, int to, int c) : from(from), to(to), c(c), f(0) {}
};

void add_edge(int from, int to, int c, vector<vector<int>> &g, vector<edge> &edges) {
    edges.emplace_back(from, to, c);
    edges.emplace_back(to, from, 0);
    edges[edges.size() - 1].inv = edges.size() - 2;
    edges[edges.size() - 2].inv = edges.size() - 1;
    g[from].emplace_back(edges.size() - 2);
    g[to].emplace_back(edges.size() - 1);
}

vector<int> p;

int find(int s, int t, vector<vector<int>> &g, vector<edge> &edges) {
    fill(p.begin(), p.end(), -1);
    p[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT32_MAX});
    int mint = 1111111;
    while (!q.empty() && p[t] == -1) {
        auto[next, minf] = q.front();
        q.pop();
        for (int ei: g.at(next)) {
            if (edges[ei].c > edges[ei].f && p[edges[ei].to] == -1) {
                q.push({edges[ei].to, min(minf, edges[ei].c - edges[ei].f)});
                p[edges[ei].to] = ei;
                if (edges[ei].to == t) {
                    mint = min(minf, edges[ei].c - edges[ei].f);
                }
            }
        }
    }
    if (p[t] == -1) return 0;
    int ei = p[t];
    while (ei != -2) {
        edges[ei].f += mint;
        edges[edges[ei].inv].f -= mint;
        ei = p[edges[ei].from];
    }
    return mint;
}

int main() {
//    freopen("in.in", "r", stdin);
//    freopen("dominoes.out", "w", stdout);
    int n, m, k, s, t;
    cin >> n >> m >> k >> s >> t;
    s--;
    t--;
    vector<pair<int, int>> redges(m);
    vector<vector<int>> g(1000000,vector<int>());
    vector<edge> edges;
    p.resize(g.size());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        redges.at(i) = {u - 1, v - 1};
    }

    int accum = 0;
    int day = 0;
    while (accum < k) {
        for (int i = 0; i < n; i++) {
            add_edge(i + n * day, i + n * (day + 1), INT32_MAX, g, edges);
        }
        for (int i = 0; i < m; i++) {
            auto[from, to] = redges.at(i);
            add_edge(from + n * day, to + n * (day + 1), 1, g, edges);
            add_edge(to + n * day, from + n * (day + 1), 1, g, edges);
        }
        int found;
        do {
            found = find(s, t + n * (day + 1), g, edges);
            accum += found;
        } while (found != 0 && accum < k);
        day++;
    }
    cout << day << '\n';

    vector<int> pos(k, s);
    for (int i = 0; i < day; i++) {
        vector<pair<int, int>> ans_line;
        for (int j = 0; j < k; j++) {
            for (int ei : g[pos[j]]) {
                if (edges[ei].f > 0) {
                    edges[ei].f--;
                    pos[j] = edges[ei].to;
                    if (edges[ei].c != INT32_MAX) {
                        ans_line.emplace_back(j + 1, pos[j] % n + 1);
                    }
                    break;
                }
            }
        }
        cout << ans_line.size() << ' ';
        for (auto[l, r] : ans_line) {
            cout << l << ' ' << r << ' ';
        }
        cout << '\n';
    }

    return 0;
}