//
// Created by natalem on 11.10.2019.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <set>
#include <stack>
#include <queue>

using namespace std;
int T = 0;
int comp = 1;

vector<int> to_output(vector<int> &res, int m = 0) {
    int cnt = 1;
    int n = res.size() - 1;
    vector<vector<int>> vec(comp, vector<int>());//todo comp+1
    vector<int> output(res.size(), 0);
    for (int i = 1; i < res.size(); i++) {
        vec[res[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (output[i]) continue;
        int prevnum = res[i];
        for (int j: vec[prevnum]) {
            output[j] = cnt;
        }
        cnt++;
    }
    return output;
}

string edge_to_str(pair<int, int> &edge) {
    return to_string(min(edge.first, edge.second)) + " " + to_string(max(edge.first, edge.second));
}

void color(int v, vector<int> &res, stack<pair<int, int>> &stack, unordered_map<string, vector<int>> &edge_to_num) {
    if (stack.empty()) return;
    while (!stack.empty()) {
        auto cur_edge = stack.top();
        stack.pop();
        for (int i : edge_to_num[edge_to_str(cur_edge)]){
            res[i] = comp;
        }
        if (cur_edge.first == v) break;
    }
    comp++;
}

void dfs(int v, int prev_v, vector<int> &time, vector<vector<int>> &edges, vector<int> &d, vector<int> &res,
         unordered_map<string, vector<int>> &edge_to_num, stack<pair<int, int>> &stack, bool is_root = true) {

    int cnt = 0;
    time[v] = T++;
    d[v] = time[v];
    for (int e : edges[v]) {
        if (e == prev_v) continue;
        if (time[e] == -1) {
            stack.push({v, e});

            cnt++;
            dfs(e, v, time, edges, d, res, edge_to_num, stack, false);
            d[v] = min(d[v], d[e]);
            if ((d[e] >= time[v] && !is_root) || (is_root && cnt > 1)) {
                color(v, res, stack, edge_to_num);
            }

        } else {
            if (time[e] < time[v]) stack.push({v, e});
            d[v] = min(d[v], time[e]);
        }
    }
    if (is_root) color(-1, res, stack, edge_to_num);
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
    unordered_map<string, vector<int>> edge_to_num;
    vector<vector<int>> edges(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        edge_to_num[to_string(a) + " " + to_string(b)].push_back(i + 1);
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }
    vector<int> time(n + 1, -1);
    vector<int> d(n + 1);
    vector<int> res(m + 1);
    stack<pair<int, int>> stack;
    for (int i = 1; i <= n; i++) {
        if (time[i] == -1 && !edges[i].empty()) {
            T = 0;
            dfs(i, -1, time, edges, d, res, edge_to_num, stack);
        }
    }
    cout << comp- 1 << "\n";
    res = to_output(res);
    for (int i = 1; i <= m; i++) {
        cout << res[i] << " ";
    }
}

