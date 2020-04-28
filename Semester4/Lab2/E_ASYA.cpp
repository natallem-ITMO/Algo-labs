#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int n, m, k, s, t;
vector<set<int>> graph;
vector<vector<int>> edges;
vector<int> stack, path;
vector<vector<pair<int, int>>> answer;

int number(int i, int v) {
    return n * i + v;
}

void read() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
//    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int a, b;
    cin >> n >> m >> k >> s >> t;
    edges = vector<vector<int>>(n + 1);
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        edges[a].emplace_back(b);
    }
    stack = vector<int>();
}

void build(int x) {
    graph = vector<set<int>>(n * (x + 1) + 1);
    for (int i = 0; i < x; ++i) {
        for (int v = 1; v <= n; ++v) {
            for (int u : edges[v]) {
                if (v == s || u == t) {
                    graph[number(i, v)].insert(number(i + 1, u));
                    continue;
                }
                if (u == s || v == t) {
                    graph[number(i, u)].insert(number(i + 1, v));
                    continue;
                }
                graph[number(i, v)].insert(number(i + 1, u));
                graph[number(i, u)].insert(number(i + 1, v));
            }
        }
    }
    path = vector<int>(n * (x + 1) + 1);
}

int bfs() {
    for (int v : graph[stack[0]]) {
        if (v % n == t % n) {
            path[v] = stack[0];
            return v;
        }
        if (!path[v]) {
            path[v] = stack[0];
            stack.emplace_back(v);
        }
    }
    stack.erase(stack.begin());
    return 0;
}

bool solve(int x) {
    for (int i = 0; i < x; ++i) {
        stack.emplace_back(number(i, s));
        path[number(i, s)] = number(i, s);
    }
    int v = 0;
    while (!stack.empty() && !v) {
        v = bfs();
    }
    if (!v) {
        return false;
    }
    while (v % n != s % n) {
        graph[path[v]].erase(v);
        graph[v].insert(path[v]);
        v = path[v];
    }
    stack.clear();
    fill(path.begin(), path.end(), 0);
    return true;
}

void dfs(int x, int number) {
    if (number % n == s % n) {
        return;
    }
    answer[(*graph[number].begin() - 1) / n].emplace_back(make_pair(x, number - (number - 1) / n * n));
    dfs(x, *graph[number].begin());
    graph[number].erase(graph[number].begin());
}

int main() {
    read();
    int l = 0, r = m + k, x, sum;
    while (l < r - 1) {
        x = (l + r) / 2;
        build(x);
        while (solve(x));
        sum = 0;
        for (int i = 1; i <= x; ++i) {
            sum += graph[number(i, t)].size();
        }
        if (sum < k) {
            l = x;
        } else {
            r = x;
        }
    }
    build(r);
    while (solve(r));
    answer = vector<vector<pair<int, int>>>(r);
    for (int i = 1; i <= r; ++i) {
        for (int v : graph[number(i, t)]) {
            answer[(v - 1) / n].emplace_back(make_pair(k, t));
            dfs(k--, v);
            if (!k) {
                break;
            }
        }
        if (!k) {
            break;
        }
    }
    cout << answer.size() << endl;
    for (const auto &v : answer) {
        cout << v.size() << "  ";
        for (auto p : v) {
            cout << p.first << " " << p.second << "  ";
        }
        cout << endl;
    }
    return 0;
}