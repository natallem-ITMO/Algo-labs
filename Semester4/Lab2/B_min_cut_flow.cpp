#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

struct edge {
    int start;
    int end;
    bool isReversed;
    edge *pair;
    int capacity;
    int number;

    edge(int start, int end, int number, bool isReversed) : start(start), end(end), isReversed(isReversed), capacity(0),
                                                            number(number) {

    }

};


edge *makeEdge(int start, int end, int capacity, int number, vector<vector<edge *>> &graph) {
    edge *curEdge1 = new edge(start, end, number, false);
    edge *revEdge1 = new edge(end, start, number, true);
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

    incomeEdge[start] = new edge(1, 2, 3, true);
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

void dfs(int v, vector<bool> &visited, vector<vector<edge *>> &graph) {
    visited[v] = true;
    for (edge *child : graph[v]) {
        if (child->capacity == 0) continue;
        int nextVertex = child->end;
        if (!visited[nextVertex]) dfs(nextVertex, visited, graph);
    }
}

set<int> getCut(vector<vector<edge *>> &graph, int start, int end, int n) {
    vector<bool> visited(n + 1, false);
    set<int> result;
    dfs(start, visited, graph);
    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            for (edge *child : graph[i]) {
                if (!visited[child->end]) result.insert(child->number);
            }
        }
    }
    return result;

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
        makeEdge(A, B, C, i + 1, graph), makeEdge(B, A, C, i + 1, graph);
    }

    int sum = 0;
    int num;
    while (num = bfs(graph, 1, n, n)) {
        sum += num;
    }
    set<int> edgesCut = getCut(graph, 1, n, n);
    cout << edgesCut.size() << " " << sum << std::endl;
    for (auto t : edgesCut){
        cout << t << " ";
    }

    return 0;
}