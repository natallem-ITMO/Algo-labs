/*
//
// Created by natalem on 17.10.2019.
//


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
using ll=long long int;
ll MAX = 10000000000;

using edge_t = vector<unordered_set<int>>;


ll findMSTnoRec(vector<pair<int, int>> &edges, vector<ll> &weight, int n, int root) {
    //   vector<ll> sum;
    ll sum = 0;
    try {
        while (true) {
            ll res = 0;
            vector<ll> minEdge(n + 1, MAX);
            for (int i = 0; i < edges.size(); i++) {
                int u = edges.at(i).first;
                int v = edges.at(i).second;
                minEdge.at(edges.at(i).second) = min(weight.at(i), minEdge.at(edges.at(i).second));
            }
            for (int i = 1; i <= n; i++) {
                if (i == root)
                    continue;
                res += minEdge.at(i);
            }
            vector<vector<int>> zeroEdges(n + 1, vector<int>());
            for (int i = 0; i < edges.size(); i++) {
                if (weight.at(i)) == minEdge.at(edges.at(i).second)) zeroEdges.(edges.at(i).first).push_back(edges.at(i).second);
            }
            sum += res;
            if (do_dfs(root, n, zeroEdges)) {
                break;
            }
            vector<int> new_components = find_components(n, zeroEdges);
            vector<pair<int, int>> new_edges;
            vector<ll> new_weight;
            for (int i = 0; i <= edges.size(); i++) {
                //u->v
                int u = edges.at(i).first;
                int v = edges.at(i).second;
                int new_comp_u = new_components.at(u);
                int new_comp_v = new_components.at(v);

                if (new_comp_u != new_comp_v) {
                    new_edges.push_back({new_comp_u, new_comp_v});
                    ll min_for_v = minEdge.at(v);
                    new_weight.push_back(weight.at(i) - min_for_v);
                }
            }
            edges = new_edges;
            weight = new_weight;
            n = new_components.at(0);
            root = new_components.at(root);
        }
    } catch (std::out_of_range & ex){
        cout<< "HERE";
    }
    return sum;
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
    vector<pair<int, int>> edges(m);
    vector<ll> weight(m);
    vector<vector<int>> input(n + 1, vector<int>());
    vector<vector<int>> output(n + 1, vector<int>());
//    vector<vector<int>> zeroEdges(n, vector<int>());//u->v
    for (int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        edges.at(i) = {a, b};
        output[a].push_back(b);
        weight.at(i) = w;
    }
    if (do_dfs(1, n, output)) {
        cout << "YES\n" << findMSTnoRec(edges, weight, n, 1);
    } else {
        cout << "NO";
    }


}*/
