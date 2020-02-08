/*
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <set>
#include <cmath>
//#include "../../../Helper/show_collections.hpp"

using namespace std;
vector<pair<int, int>> coords;
int MAX = 10000000;

float get_edge(int i, int j) {
    int x = coords[i].first - coords[j].first;
    int y = coords[i].second - coords[j].second;
    return sqrt(x * x + y * y);
}

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    coords.push_back({0, 0});
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        coords.push_back({x, y});
    }
    //   vector<unordered_map<int, float>> edges(n+1);
    /* for (int i = 1; i <= n; i++) {
         for (int j = 1; j < i; j++) {
             int x = coords[i].first - coords[j].first;
             int y = coords[i].second - coords[j].second;
             edges[j][i] = sqrt(x * x + y * y);
         }
     }*/

    unordered_set<int> B(n - 1);
    for (int i = 2; i <= n; ++i) {
        B.insert(i);
    }
    vector<float> weight_to_vertex(n + 1);
//    set<float> min_edges;
//    unordered_map<float, unordered_set<int>> value_edge_to_v;
    for (int i = 2; i <= n; i++) {
        weight_to_vertex[i] = get_edge(1, i);
    }
    float res = 0;
    while (!B.empty()) {
        float min_w = MAX;
        int v = -1;
        for (int u: B) {
            if (min_w > weight_to_vertex[u]) {
                min_w = weight_to_vertex[u];
                v = u;
            }
        }
        res += min_w;
        B.erase(v);
        for (int u : B) {
            weight_to_vertex[u] = min(weight_to_vertex[u], get_edge(u, v));
        }
    }
    cout.precision(17);
    cout << res;
}