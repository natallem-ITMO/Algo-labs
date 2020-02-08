//
// Created by natalem on 27.10.2019.
//

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
//unsigned long long int MAX = ULLONG_MAX;
long long int MAX2 = (long long int) 400000 * 30000 + 2;

void add(int v, long long int w, map<long long int, vector<int>> &vs) {
    if (vs.find(w) == vs.end()) {
        vs[w] = vector<int>();
    }
    vs[w].push_back(v);
}

int get_min(map<long long int, vector<int>> &vs) {
    vector<int> &minimals = vs.begin()->second;
    int ans = minimals[minimals.size() - 1];
    if (minimals.size() == 1) {
        vs.erase(vs.begin());
    } else {
        minimals.pop_back();
    }
    return ans;
}

void remove_v(int v, long long int w, map<long long int, vector<int>> &vs) {
    auto itr= vs.find(w);
    vector<int> &vector = itr->second;
    if (vector.size() == 1) {
        vs.erase(itr);
        return;
    }
    for (auto i = vector.begin(); i != vector.end(); i++){
        if ((*i)==v) {
            vector.erase(i);
            return;
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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> edges(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[a].push_back({b, w});
        edges[b].push_back({a, w});
    }
    //vector<bool> visited(n + 1, false);
    map<long long int, vector<int>> mapv;
    vector<long long int> d(n + 1, MAX2);
    d[1] = 0;
    for (int i = 1; i <= n; i++) {
        add(i, d[i], mapv);
    }
    for (int i = 1; i <= n; i++) {
        int min_v = get_min(mapv);
        for (auto pair : edges[min_v]) {
            int u = pair.first;
            int w = pair.second;
            if (d[u] > d[min_v] + w){
                remove_v(u,d[u], mapv);
                d[u] =  d[min_v] + w;
                add(u,d[u],mapv);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << d[i] << " ";
    }
}