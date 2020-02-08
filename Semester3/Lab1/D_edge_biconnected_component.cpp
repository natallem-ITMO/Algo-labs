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

void update_result(vector<int> &res, stack<int> &stack, int v = -1) {
    while (!stack.empty()) {
        int cur_v = stack.top();
        stack.pop();
        if (cur_v == v) {
            res[v] = comp;
            break;
        }
        res[cur_v] = comp;
    }
    comp++;
}

void dfs(int v, int prev_v, vector<int> &time, vector<unordered_map<int,int>> &edges, vector<int> &d, vector<int> &res,
         stack<int> &stack) {
    stack.push(v);
    time[v] = T++;
    d[v] = time[v];
    for (auto & ed : edges[v]) {
        int e = ed.first;
        if (e == prev_v && ed.second==1) continue;
        if (time[e] == -1) {
            dfs(e, v, time, edges, d, res, stack);
            d[v] = min(d[v], d[e]);
            if (d[e] == time[e]) {
                update_result(res, stack, e);
            }
        } else {
            d[v] = min(d[v], time[e]);
        }
    }
    int x = 10;

}

vector<int> to_output(vector<int> &res) {
    int cnt = 1;
    int n = res.size() - 1;
    vector<vector<int>> vec(comp + 1, vector<int>());
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
    vector<unordered_map<int,int>> edges(n + 1, unordered_map<int,int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            edges[a][b]++;
            edges[b][a]++;
        }
    }
    vector<int> time(n + 1, -1);
    vector<int> d(n + 1);
    vector<int> res(n + 1);
    stack<int> stack;
    for (int i = 1; i <= n; i++) {
        if (time[i] == -1) {
            T = 0;
            dfs(i, -1, time, edges, d, res, stack);
            update_result(res, stack);
        }
    }
    comp--;
    cout << comp << "\n";

    res = to_output(res);

    for (int i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
}

