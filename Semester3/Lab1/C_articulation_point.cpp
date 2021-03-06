//
// Created by natalem on 11.10.2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <set>
#include <queue>

using namespace std;
int T = 0;

void dfs( int v, int prev_v, vector<int> &time, vector<vector<int>> &edges, vector<int> &d, set<int> &res,
         unordered_map<string, int> &str_num_input_edges, bool is_root = true) {
    int cnt = 0;
    time[v] = T++;
    d[v] = time[v];
    for (int e : edges[v]) {
        if (e == prev_v) continue;
        if (time[e] == -1) {
            cnt++;
            dfs(e, v, time, edges, d, res, str_num_input_edges, false);
            d[v] = min(d[v], d[e]);
            if (d[e] >= time[v] && !is_root)
                res.insert(v);
        } else {
            d[v] = min(d[v], time[e]);
        }
    }
    if (is_root && cnt>1)
        res.insert(v);
}


int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//todo many comp svazn
    int n, m;
    cin >> n >> m;
    unordered_map<string, int> str_num_input_edges;
    vector<vector<int>> edges(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        str_num_input_edges[to_string(a) + " " + to_string(b)] = i + 1;
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }
    vector<int> time(n + 1, -1);
    vector<int> d(n + 1);
    set<int> res;
    for (int i = 1; i <= n; i++) {
        if (time[i] == -1 && !edges[i].empty()) {
            T = 0;
            dfs(i, -1, time, edges, d, res, str_num_input_edges);
        }
    }
    cout << res.size() << "\n";
    for (int i : res) {

        cout << i << "\n";
    }

}

