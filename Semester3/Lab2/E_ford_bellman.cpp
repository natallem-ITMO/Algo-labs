#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <climits>
#include <set>
#include <list>
//#include "../../../Helper/show_collections.hpp"

using namespace std;
using ll = long long int;
using edgesT=vector<vector<pair<int, ll>>>;

ll INF = LLONG_MAX;
ll _INF = LLONG_MIN;
int n, m, s;


struct edge {
    int u, v;
    ll w;
};

void ford_bellman(edgesT &edges, vector<ll> & d, vector<int> & p) {

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            for (pair<int, ll> pair : edges[j]) {
                int to = pair.first;
                ll w = pair.second;
                int a = d[to];
                int b = d[j]+w;
                if ((d[j] < INF) && (d[to] > d[j] + w)) {
                    d[to] = d[j] + w;
                    p[to] = j;
                }
            }
        }
    }
//    show_collection(p);
//    show_collection(d);

}

void dfs(int u, edgesT & edges, vector<bool> & used){
    used[u] = true;
    for (auto pair : edges[u]){
        int v = pair.first;
        if (!used[v]) dfs(v, edges, used);
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
//    int n,m,s;
    cin >> n >> m >> s;
    vector<vector<pair<int, ll>>> edges(n+1, vector<pair<int, ll>>());
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges[u].push_back({v,w});
    }
    vector<ll> d(n + 1, INF);
    d[s] = 0;
    vector<int> p(n + 1, -1);
    ford_bellman(edges,d,p);
    vector<bool> used(n+1, false);
    for (int j = 1; j <= n; j++){
        for (pair<int, ll> pair : edges[j]) {
            int to = pair.first;
            ll w = pair.second;
            if ((d[j] < INF) && (d[to] > d[j] + w) && !used[to]) {
                dfs(j, edges, used);
            }
        }
    }
    for (int i = 1; i <= n; i++){
        if (used[i]) cout << "-\n";
        else if (d[i]==INF) cout << "*\n";
        else cout << d[i] << "\n";
    }


};