

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
//#include <list>
#include <fstream>
#include <queue>
#include <list>

using namespace std;
using ll = long long int;

void fall() {
    vector<int> v;
    cout << v[10];
};

struct node {
    list<pair<int, int>> edges;
    ll grandi = -1;

    node() {
        edges.resize(0);
    }
};

ll grandi(int v, vector<node> &nodes) {
    if (nodes[v].edges.empty()) {
        nodes[v].grandi = 0;
        return 0;
    } else {
        ll xr = 0;
        for (auto &child : nodes[v].edges) {
            xr ^= (grandi(child.first, nodes) + 1);
        }
        nodes[v].grandi = xr;
        return xr;
    }
}

void orient_edges(int cur, int prev, vector<node> &nodes) {
    if (nodes[cur].edges.empty()) return;
    node &nn = nodes[cur];

    auto itr_del = nodes[cur].edges.end();
    auto itr = nodes[cur].edges.begin();
    for (; itr != nodes[cur].edges.end(); itr++) {
        if (itr->first == prev) {
            itr_del = itr;
        } else {
            orient_edges(itr->first, cur, nodes);
        }
    }
    if (itr_del != nodes[cur].edges.end()) nodes[cur].edges.erase(itr_del);
}

int find_edge(int cur, ll need, vector<node> &nodes) {
    if (nodes[cur].grandi == need) {
        {
            return -1;
        }
    }
    if (nodes[cur].edges.empty()) {
        return -1;
    }
    node &node = nodes[cur];
    ll curGrandi = node.grandi;
    for (auto edge: nodes[cur].edges) {
        int v = edge.first;
        ll vGrandiToU = nodes[v].grandi + 1;
        ll nextNeed = need ^(curGrandi ^ vGrandiToU);
        if (nextNeed == 0) return edge.second;
        if (nextNeed < vGrandiToU) {
            return find_edge(v, nextNeed - 1, nodes);
        }
        if (vGrandiToU > curGrandi) {
            continue;
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
    int n, r;
    //fall();
    cin >> n >> r;
    vector<node> nodes(n + 1);

    for (int i = 1; i < n; i++) {
        node curNode;
        int a, b;
        cin >> a >> b;
        nodes[a].edges.push_back({b, i});
        nodes[b].edges.push_back({a, i});
    }
    orient_edges(r, -1, nodes);
    grandi(r, nodes);
    if (nodes[r].grandi == 0) {
        cout << 2;
    } else {
        cout << "1\n";

        cout << find_edge(r, 0, nodes);
        int x = 10;
    }


}