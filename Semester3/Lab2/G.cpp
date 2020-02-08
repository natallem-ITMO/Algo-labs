#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <fstream>
#include <string>
#include <climits>

using namespace std;
using ll =  long long;

namespace std {
    template<>
    struct hash<pair<int, int>> {
        std::size_t operator()(const pair<int, int> &c) const {
            return std::hash<std::string>()(to_string(c.first) + " " + to_string(c.second));
        }
    };
}

int MAX = 100000;
ll INF = LONG_LONG_MAX;


vector<ll> deikstra(int n, int start, vector<vector<pair<int, int>>> &edges) {
    vector<ll> d(n+1, INF);
    d[1] = 0;
    set<pair<ll, int>> B;
    B.insert({0, start});
    while (!B.empty()) {
        auto minPairPtr = B.begin();
        int min_v = minPairPtr->second;
        ll min_w = minPairPtr->first;
        B.erase(minPairPtr);
        if (min_w > d[min_v]) continue;
        for (auto &pair : edges[min_v]) {
            int u = pair.first;
            ll w = pair.second;
            if (d[u] > d[min_v] + w) {
                B.erase({u, d[u]});
                d[u] = d[min_v] + w;
                B.insert({d[u], u});
            }
        }
    }
    return d;
}

void dfs(int v, vector<bool> &used, vector<vector<pair<int, int>>> &edges) {
    used[v] = true;
    for (auto pair : edges[v]) {
        if (!used[pair.first]) dfs(pair.first, used, edges);

    }
}

void imp() {
    cout << "Impossible";
}

void pos() {
    cout << "Possible";
}

vector<vector<pair<int, int>>> createGraph(int mod, int n, vector<vector<pair<int, int>>> &edges, ll t) {
    int maxAmountOfNewEdges = mod * n+4;
    vector<pair<int, int>> idPair(1, {-1, -1});
    vector<vector<int>> pairId(n + 1, vector<int>(mod + 1, 0));
    vector<vector<pair<int, int>>> newEdges(maxAmountOfNewEdges + 1);
    pair<int, int> first = {1, 0};
    pairId[1][0] = 1;
    vector<int> queue;
    idPair.push_back(first);
    queue.push_back(1);
    while (!queue.empty()) {
        int id = queue.back();
        queue.pop_back();
        pair<int, int> curPair = idPair[id];
        int originalVertex = curPair.first;
        int curVertexMod = curPair.second;
        for (auto myPair: edges[originalVertex]) {
            int edgeWeight = myPair.second;
            pair<int, int> nextVertex = {myPair.first, (curVertexMod + edgeWeight) % mod};
            int x = nextVertex.first;
            int y = nextVertex.second;

            if (pairId[nextVertex.first][nextVertex.second] != 0) {
                newEdges[id].push_back({pairId[nextVertex.first][nextVertex.second], edgeWeight});
            } else {
                int nextIndex = idPair.size();
                idPair.push_back(nextVertex);
                pairId[nextVertex.first][nextVertex.second] = nextIndex;
                queue.push_back(nextIndex);
                newEdges[id].push_back({pairId[nextVertex.first][nextVertex.second], edgeWeight});

            }
        }
    }
    newEdges[0].push_back({idPair.size() - 1, pairId[n][t % mod]});
    return newEdges;
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
    int minEdge = MAX;
    int maxEdge = 0;
    vector<vector<pair<int, int>>> edges(n + 1, vector<pair<int, int>>());

    for (int i = 0; i < m; i++) {
        int a, b;
        int w;
        cin >> a >> b >> w;
        if (a == 1 || b == n || a == n || b == 1) minEdge = min(minEdge, w);
        maxEdge = max(maxEdge, w);
        edges[a].push_back({b, w});
        edges[b].push_back({a, w});
    }
    ll t;
    cin >> t;
    vector<bool> used(n + 1, false);
    dfs(1, used, edges);
    if (!used[n]) {
        imp();
        return 0;
    }
    int mod = minEdge * 2;
    vector<vector<pair<int, int>>> newEdges = createGraph(mod, n, edges, t);
    int idTarget = newEdges[0][0].second;
    vector<ll> d = deikstra(newEdges[0][0].first, 1, newEdges);
    ll res = d[idTarget];
    if (res <= t) {
        pos();
        return 0;
    }
    imp();
    return 0;
}