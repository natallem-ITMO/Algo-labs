#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct edge {
    int start;
    int end;
    bool isReversed;
    edge *pair;
    int capacity;

    edge(int start, int end, bool isReversed) : start(start), end(end), isReversed(isReversed), capacity(0) {

    }

};


edge *makeEdge(int start, int end, int capacity, vector<vector<edge *>> &graph) {
    edge *curEdge1 = new edge(start, end, false);
    edge *revEdge1 = new edge(end, start, true);
    curEdge1->capacity = capacity;
    revEdge1->capacity = 0;
    curEdge1->pair = revEdge1;
    revEdge1->pair = curEdge1;
    graph[start].push_back(curEdge1);
    graph[end].push_back(revEdge1);
    return curEdge1;
}

int bfs(vector<vector<edge *>> &graph, int start, int end, int n) {
    if (start == end) return 0;
    queue<int> vertexes;
    vector<edge *> incomeEdge(n + 1, nullptr);

    incomeEdge[start] = new edge(1, 2, true);
    vertexes.push(start);
    bool done = false;
    while (!vertexes.empty() && !done) {
        int currentVertex = vertexes.front();
        vertexes.pop();
        for (edge *child : graph[currentVertex]) {
            if (child->capacity == 0) continue;
            int nextVertex = child->end;
            if (incomeEdge[nextVertex] == nullptr) {
                incomeEdge[nextVertex] = child;
                if (nextVertex == end) {
                    done = true;
                    break;
                }
                vertexes.push(nextVertex);
            }
        }
    }
    int sum = 0;
    if (incomeEdge[end] != nullptr) {
        int parent = end;
        sum = incomeEdge[parent]->capacity;
        while (parent != start) {
            sum = min(sum, incomeEdge[parent]->capacity);
            parent = incomeEdge[parent]->start;
        }
        parent = end;
        while (parent != start) {
            incomeEdge[parent]->capacity -= sum;
            incomeEdge[parent]->pair->capacity += sum;
            parent = incomeEdge[parent]->start;
        }
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

    int n;
    int m;
    cin >> n >> m;
    vector<vector<edge *>> graph(n + 1, vector<edge *>());
    vector<pair<edge *, edge *>> edges;
    vector<int> capacities;

    for (int i = 0; i < m; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        capacities.push_back(C);
        edges.emplace_back(makeEdge(A, B, C, graph), makeEdge(B, A, C, graph));
    }

    int sum = 0;
    int num;
    while (num = bfs(graph, 1, n, n)) {
        sum += num;
    }

    cout << sum << std::endl;
    for (int i = 0; i < m; i++) {
        int cap_forward = edges[i].first->capacity;
        int cap_reverse = edges[i].second->capacity;
        if (cap_forward < capacities[i]) {
            cout << capacities[i] - cap_forward << "\n";
        } else
        if (cap_reverse < capacities[i]) {
            cout << -(capacities[i] - cap_reverse) << "\n";
        } else {
            cout << 0 << "\n";
        }
    }

    return 0;
}
