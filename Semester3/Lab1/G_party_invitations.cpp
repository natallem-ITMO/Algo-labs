//
// Created by natalem on 11.10.2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

#include <set>
#include <stack>
#include <queue>
//#include "../../../Helper/show_collections.hpp"

using namespace std;
using edge_t = vector<unordered_set<int>>;
int mod;

int reverse_vertex(int v) {
    return (v > mod) ? v - mod : v + mod;
}

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

vector<int> get_components(int n, vector<vector<int>> &edges, vector<pair<int, int>> &res_edges) {
    edge_t str_edges(n + 1, unordered_set<int>());
    edge_t rev_edges(n + 1, unordered_set<int>());
    int m = edges.size();
    for (int i = 0; i < m; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        if (a == b) continue;
        str_edges[a].insert(b);
        rev_edges[b].insert(a);
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
    vector<int> num_components(n + 1, 0);//vertex_num -> num of new component
    for (int i = 1; i <= n; i++) {
        num_components[order[i]] = num_components_order[i];
    }
    unordered_set<string> new_edges;
    for (int v = 1; v <= n; v++) {
        for (int u : str_edges[v]) {
            int v_comp = num_components[v];
            int u_comp = num_components[u];
            if (v_comp == u_comp) continue;
            string edge_c = to_string(v_comp) + " " + to_string(u_comp);
            auto t = new_edges.insert(edge_c);
            if (t.second)
                res_edges.push_back({v_comp, u_comp});
        }
    }
    num_components[0] = --timer;
    return num_components;
}


bool do_sort(vector<vector<int>> &edges, vector<int> &cnt, vector<int> &res, int N, queue<int> &q) {
    for (int i = 0; i < N; i++) {
        if (q.empty()) return false;
        int v = q.front();
        q.pop();
        for (int u : edges[v]) {
            cnt[u]--;
            if (cnt[u] == 0) q.push(u);
        }
        res[i] = v;
    }
    return true;
}

vector<int> top_sort(int n, vector<pair<int, int>> &input_edges) {
    int N, M;
    N = n;
    M = input_edges.size();
    vector<vector<int>> edges(N + 1, vector<int>());
    vector<int> cnt(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int u, v;
        u = input_edges[i].first;
        v = input_edges[i].second;
        ++cnt[v];
        edges[u].emplace_back(v);
    }
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (cnt[i + 1] == 0) q.push(i + 1);
    }
    vector<int> res(N);

    do_sort(edges, cnt, res, N, q);
    return res;
}

void do_task() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    mod = n;
    int N = n + 1;
    unordered_map<string, int> names_v;
    vector<string> v_names(n + 1);
    for (int i = 1; i <= n; i++) {
        string name;
        cin >> name;
        names_v[name] = i;
        v_names[i] = name;
    }
    vector<vector<int>> edges;

    for (int i = 0; i < m; i++) {
        string n1, n2;
        cin >> n1 >> n2 >> n2;
        int e1, e2;
        if (n1[0] == '-') {
            e1 = reverse_vertex(names_v[n1.substr(1)]);
        } else e1 = names_v[n1.substr(1)];
        if (n2[0] == '-') {
            e2 = reverse_vertex(names_v[n2.substr(1)]);
        } else e2 = names_v[n2.substr(1)];
        edges.push_back({e1, e2});
        edges.push_back({reverse_vertex(e2), reverse_vertex(e1)});
    }
    vector<pair<int, int>> edges_condensation;
    vector<int> v_comp = get_components(2 * n, edges, edges_condensation);
    int amount_components = v_comp[0];
    vector<int> top_sorted = top_sort(amount_components, edges_condensation);

    for (int i = 1; i < n; i++) {
        if (v_comp[i] == v_comp[reverse_vertex(i)]) {
            cout << "-1";
            return;
        }
    }

    vector<unordered_set<int>> get_vertices_in_component(amount_components + 1, unordered_set<int>());
    for (int i = 1; i <= 2 * n; i++) {
        get_vertices_in_component[v_comp[i]].insert(i);
    }

    vector<int> components_pair(amount_components + 1, 0);
    for (int i = 1; i <= amount_components; i++) {
        components_pair[i] = v_comp[reverse_vertex(*get_vertices_in_component[i].begin())];
    }
    vector<int> value_of_components(amount_components + 1, -1);
    for (int i = top_sorted.size() - 1; i >= 0; i--) {
        int cur_component = top_sorted[i];
        if (value_of_components[cur_component] != -1) continue;
        value_of_components[cur_component] = 1;
        value_of_components[components_pair[cur_component]] = 0;
    }
    set<int> result_list;
    for (int i = 1; i <= amount_components; i++) {
        if (!value_of_components[i]) continue;
        for (int v : get_vertices_in_component[i]) {
            if (v <= n)
                result_list.insert(v);
        }
    }
    cout << result_list.size() << "\n";
    for (int i : result_list) {
        cout << v_names[i] << "\n";
    }

    int x = 10;


}


int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    do_task();


}

