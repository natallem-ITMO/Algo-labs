#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;
int n, m;
using ull = unsigned long long;
ull INF = ULLONG_MAX;

struct edge {
    int start;
    int end;
    bool isReversed;
    edge *pair;
    int capacity;
    int flow;
    int cost;

    int getC() {
        return capacity - flow;
    }

    bool isValid() {
        return capacity - flow > 0;
    }

    edge(int start, int end, bool isReversed) : start(start), end(end), isReversed(isReversed), capacity(0), flow(0) {}

};

edge *makeEdge(int start, int end, int capacity, int cost, vector<vector<edge *>> &graph) {
    edge *curEdge = new edge(start, end, false);
    edge *revEdge = new edge(end, start, true);
    curEdge->capacity = capacity;
    curEdge->flow = 0;
    revEdge->capacity = 0;
    revEdge->flow = 0;
    curEdge->pair = revEdge;
    revEdge->pair = curEdge;
    curEdge->cost = cost;
    revEdge->cost = -cost;
    graph[start].push_back(curEdge);
    graph[end].push_back(revEdge);
    return curEdge;
}

ull getSuperCost(edge *&pEdge, vector<ull> &potentials) {
    return (pEdge->cost + potentials[pEdge->start]) - potentials[pEdge->end];
}

void fall() {
    vector<int> n;
    cout << n[10];

}

vector<edge *>
setPotentialAndGiveShortestPath(vector<ull> &potentials, vector<vector<edge *>> &graph, int start, int end) {
    vector<edge *> res;
    vector<bool> used(n + 1, false);
    vector<edge *> cameFrom(n + 1, nullptr);
    vector<ull> d(n + 1, INF);
    d[start] = 0;

    for (int i = 1; i < graph.size(); i++) {
        int v = -1;
        for (int j = 1; j < graph.size(); j++) {
            if (!used[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }
        if (d[v] == INF) break;
        used[v] = true;
        for (auto &ed : graph[v]) {
            if (ed->isValid()) {
                ull newCost = getSuperCost(ed, potentials) + d[v];
                if (newCost < d[ed->end]) {
                    d[ed->end] = newCost;
                    cameFrom[ed->end] = ed;
                }
            }
        }
    }
    if (cameFrom[end] == nullptr)
        return res;
    res.push_back(cameFrom[end]);
    int cameFromVertex = cameFrom[end]->start;
    while (cameFromVertex != start) {
        res.push_back(cameFrom[cameFromVertex]);
        cameFromVertex = (*(--res.end()))->start;
    }
    reverse(res.begin(), res.end());
    for (int i = 1; i <= n; i++) {
        if (d[i] == INF) {
            fall();
        }
        potentials[i] += d[i];
    }
    return res;
}

ull applyPathToGraph(vector<edge *> &path, vector<vector<edge *>> &graph) {
    ull sum = 0;
    ull minFutureFlow = INF;
    for (auto &ed : path) {
        if (ed->getC() < minFutureFlow) {
            minFutureFlow = ed->getC();
        }
    }
    for (auto &ed : path) {
        ed->flow += minFutureFlow;
        ed->pair->flow -= minFutureFlow;
        sum += ed->cost * minFutureFlow;
    }
    return sum;
}

ull findMaxFlowMinCost(vector<vector<edge *>> &graph, int start, int end) {
    ull sum = 0;
    vector<ull> potentials(n + 1, 0);

    auto path = setPotentialAndGiveShortestPath(potentials, graph, start, end);
    while (!path.empty()) {
        sum += applyPathToGraph(path, graph);
        path = setPotentialAndGiveShortestPath(potentials, graph, start, end);
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
    int N;
    cin >> N;
    n = N*2 + 2;
    int start = 2 * N + 1;
    int end = 2 * N + 2;
    vector<vector<edge *>> graph(n + 1, vector<edge *>());
    for (int i = 1; i <= N; i++){
        for (int j = N+1; j <=N+N; j++){
            int cost;
            cin >> cost;
            makeEdge(i, j, 1, cost, graph);
        }
    }
    for (int i = 1; i <= N; i++){
        makeEdge(start, i, 1, 0, graph);
    }
    for (int i = N+1; i <= N+N;i++){
        makeEdge(i, end, 1, 0, graph);
    }



    cout << findMaxFlowMinCost(graph, start, end) << "\n";
    for (int i = 1; i <= N; i++){
        for (auto ed : graph[i]){
            if (!ed->isReversed && ed->flow==1){
                cout << i << " " << (ed->end)-N<< "\n";
                break;
            }
        }
    }

    return 0;
}
