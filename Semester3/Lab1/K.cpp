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

int dfs(int v, vector<bool> &visited, vector<int> &res, edge_t &edges) {
    visited[v] = true;
    for (int e : edges[v]) {
        if (!visited[e]) dfs(e, visited, res, edges);
    }
    res.push_back(v);
}

void find_component(int v, int timer, edge_t &edges, vector<int> &components,
                    vector<int> &v_to_order_pos) {
    components[v_to_order_pos[v]] = timer;
    for (int i : edges[v])
        if (!components[v_to_order_pos[i]])
            find_component(i, timer, edges, components, v_to_order_pos);

}


vector<int> find_components(int n, vector<vector<int>> &edges) {
    int m = edges.size();

    edge_t str_edges(n + 1, unordered_set<int>());
    edge_t rev_edges(n + 1, unordered_set<int>());

    for (int a = 1; a < edges.size(); a++) {
        for (int b : edges[a]) {
            //   if (a == b) continue;
            str_edges[a].insert(b);
            rev_edges[b].insert(a);
        }
    }

    vector<bool> visited(n + 1, false);
    vector<int> order(1, -1);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i, visited, order, str_edges);
    }
    vector<int> v_to_order_pos(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        v_to_order_pos[order[i]] = i;
    }
    vector<int> num_components_order(order.size(), 0);
    int timer = 1;
    for (int i = n; i > 0; i--) {
        if (!num_components_order[i])
            find_component(order[i], timer++, rev_edges, num_components_order, v_to_order_pos);
    }
    vector<int> num_components(n + 1, 0);//vertex_num -> num in new component
    num_components[0] = timer - 1;

    for (int i = 1; i <= n; i++) {
        num_components[order[i]] = num_components_order[i];
    }
    return num_components;
}


void dfs(int root, vector<vector<int>> &edges, vector<bool> &visited) {
    visited[root] = true;
    for (int u : edges[root]) {
        if (!visited[u]) dfs(u, edges, visited);
    }
}

bool do_dfs(int root, int n, vector<vector<int>> &zeroEdges) {
    vector<bool> visited(n + 1, false);
    dfs(root, zeroEdges, visited);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) return false;
    }
    return true;
}

/*
ll findMSTnoRec(vector<pair<int, int>> &edges, vector<ll> &weight, int n, int root) {
    //   vector<ll> sum;
    ll sum = 0;
   try {
       while (true) {
           ll res = 0;
           vector<ll> minEdge(n + 1, MAX);
           for (int i = 0; i < edges.size(); i++) {
               int u = edges[i].first;
               int v = edges[i].second;
               minEdge[edges[i].second] = min(weight[i], minEdge[edges[i].second]);
           }
           for (int i = 1; i <= n; i++) {
               if (i == root)
                   continue;
               res += minEdge[i];
           }
           vector<vector<int>> zeroEdges(n + 1, vector<int>());
           for (int i = 0; i < edges.size(); i++) {
               if (weight[i] == minEdge[edges[i].second]) zeroEdges[edges[i].first].push_back(edges[i].second);
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
               int u = edges[i].first;
               int v = edges[i].second;
               int new_comp_u = new_components[u];
               int new_comp_v = new_components[v];

               if (new_comp_u != new_comp_v) {
                   new_edges.push_back({new_comp_u, new_comp_v});
                   ll min_for_v = minEdge[v];
                   new_weight.push_back(weight[i] - min_for_v);
               }
           }
           edges = new_edges;
           weight = new_weight;
           n = new_components[0];
           root = new_components[root];
       }
   } catch (std::out_of_range & ex){
       cout<< "HERE";
   }
    return sum;
}
*/
ll findMSTnoRec(vector<pair<int, int>> &edges, vector<ll> &weight, int n, int root) {
    //   vector<ll> sum;
    ll sum = 0;
    while (true) {
        vector<ll> minEdge(n + 1, MAX);
        vector<vector<int>> zeroEdges(n + 1, vector<int>());

        ll res = 0;

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
        for (int i = 0; i < edges.size(); i++) {
            if (weight.at(i) == minEdge.at(edges.at(i).second))
                zeroEdges.at(edges.at(i).first).push_back(edges.at(i).second);
        }
        sum += res;
        if (do_dfs(root, n, zeroEdges)) {
            break;
        }

//from here
        vector<int> new_components = find_components(n, zeroEdges);
        vector<pair<int, int>> new_edges;
        vector<ll> new_weight;



            for (int i = 0; i </*=*/ edges.size(); i++) {
               /*try {
                int u = edges.at(i).first;
                int v = edges.at(i).second;
                } catch (std::out_of_range &ex) {
                    cout << "HERE";
                    return 0;
                }*/int u = edges.at(i).first;
                int v = edges.at(i).second;
                int new_comp_u = new_components.at(u);
                int new_comp_v = new_components.at(v);


//                int new_comp_u = new_components.at(u);
//                int new_comp_v = new_components.at(v);
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
            edges[i] = {a, b};
            output[a].push_back(b);
            weight[i] = w;
        }
        if (do_dfs(1, n, output)) {
            cout << "YES\n" << findMSTnoRec(edges, weight, n, 1);
        } else {
            cout << "NO";
        }


    }