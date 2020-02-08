//
// Created by natalem on 11.10.2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

#include <set>
#include <stack>
#include <queue>

using namespace std;
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
//    else return;
    for (int i : edges[v])
        if (!components[v_to_order_pos[i]])
            find_component(i, timer, edges, components, v_to_order_pos);
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

    edge_t str_edges(n + 1, unordered_set<int>());
    edge_t rev_edges(n + 1, unordered_set<int>());

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a == b) continue;
        str_edges[a].insert(b);
        rev_edges[b].insert(a);
    }

    vector<bool> visited(n + 1, false);
    vector<int> order(1,-1);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i, visited, order, str_edges);
    }
    vector<int> v_to_order_pos(n+1,-1);
    for (int i = 1 ; i<= n; i++){
        v_to_order_pos[order[i]] = i;
    }
    vector<int> num_components_order(order.size(), 0);
    int timer = 1;
    for (int i = n; i > 0; i--) {
        if (!num_components_order[i])
            find_component(order[i], timer++, rev_edges, num_components_order, v_to_order_pos);
    }
    vector<int> num_components(n+1, 0);//vertex_num -> num of new component
    for (int i =1; i <= n; i++){
        num_components[order[i]] = num_components_order[i];
    }
    unordered_set<string> new_edges;
    for (int v = 1; v <= n; v++){
        for (int  u : str_edges[v]){
            int v_comp = num_components[v];
            int u_comp = num_components[u];
            if (v_comp==u_comp) continue;
            string edge_c = to_string(v_comp)+ " "+to_string(u_comp);
            new_edges.insert(edge_c);
        }
    }
    cout << new_edges.size();
}

