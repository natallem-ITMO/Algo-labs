
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

#include <set>
//#include "../../../Helper/show_collections.hpp"

using namespace std;
int MAX = 1000001;
// u->v

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<unordered_map<int, int>> edges(n + 1, unordered_map<int, int>());
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == v) continue;
        if (edges[u].find(v) != edges[u].end()) {
            edges[u][v] = min(edges[u][v], w);
        } else edges[u][v] = w;
        swap(u, v);
        if (edges[u].find(v) != edges[u].end()) {
            edges[u][v] = min(edges[u][v], w);
        } else edges[u][v] = w;

    }
    unordered_set<int> A({1});
    unordered_set<int> B(n - 1);
    for (int i = 2; i <= n; ++i) {
        B.insert(i);
    }
    vector<int> weight_to_vertex(n + 1, MAX);
    set<int> min_edges;
    unordered_map<int, unordered_set<int>> value_edge_to_v;
    for (pair<int, int> pair : edges[1]) {
        min_edges.insert(pair.second);
        value_edge_to_v[pair.second].insert(pair.first);
        weight_to_vertex[pair.first] = pair.second;
    }
    long long unsigned res = 0;
    while (!B.empty()) {
        int min_w = *min_edges.begin();
        int v = *value_edge_to_v[min_w].begin();
        A.insert(v);
        res += min_w;
        B.erase(v);
        value_edge_to_v[min_w].erase(v);
        if (value_edge_to_v[min_w].empty()) min_edges.erase(min_w);
        for (pair<int, int> p : edges[v]) {
            int u = p.first;
            int w = p.second;
            int cur_w = weight_to_vertex[u];
            if (B.find(u) != B.end() && w < cur_w) {
                value_edge_to_v[cur_w].erase(u);
                if (value_edge_to_v[cur_w].empty()) min_edges.erase(cur_w);
                weight_to_vertex[u] = w;
                min_edges.insert(w);
                value_edge_to_v[w].insert(u);
            }
        }
    }
    cout << res;
}