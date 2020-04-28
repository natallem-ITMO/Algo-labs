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
    int flow;

    int getC() {
        return capacity - flow;
    }

    edge(int start, int end, bool isReversed) : start(start), end(end), isReversed(isReversed), capacity(0), flow(0) {}

};


edge *makeEdge(int start, int end, int capacity, vector<vector<edge *>> &graph) {
    edge *curEdge1 = new edge(start, end, false);
    edge *revEdge1 = new edge(end, start, true);
    curEdge1->capacity = capacity;
    curEdge1->flow = 0;
    revEdge1->capacity = 0;
    revEdge1->flow = 0;
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
            if (child->getC() == 0) continue;
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
        sum = incomeEdge[parent]->getC();
        while (parent != start) {
            sum = min(sum, incomeEdge[parent]->getC());
            parent = incomeEdge[parent]->start;
        }
        parent = end;
        while (parent != start) {
            incomeEdge[parent]->flow += sum;
            incomeEdge[parent]->pair->flow -= sum;
            parent = incomeEdge[parent]->start;
        }
    }

    return sum;
}

bool dfs(int v, vector<int> &path, vector<bool> &visited, vector<vector<edge *>> &graph, int end) {
    visited[v] = true;
    if (v==end) return true;
    for (edge *child : graph[v]) {
        if (!child->isReversed && (child->flow == 1) && !visited[child->end]){
            path.push_back(child->end);
            if (dfs(child->end, path, visited, graph, end)) {
                child->flow = 0;
                return true;
            }
            path.pop_back();
        }
    }
    return false;
}

vector<int> createPath(vector<vector<edge *>> &graph, int start, int end, int n) {
    vector<int> path;
    vector<bool> visited(n + 1, false);
    path.push_back(start);
    dfs(start, path, visited, graph, end);
    return path;
}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<edge *>> graph(n + 1, vector<edge *>());

    vector<int> capacities;

    for (int i = 0; i < m; i++) {
        int A, B;
        cin >> A >> B;
        if (A==B) continue;
        makeEdge(A, B, 1, graph);
    }

    int sum = 0;
    int num;
    for (int i = 0; i < 2; i++) {
        sum += bfs(graph, s, t, n);
    }
    if (sum < 2) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    for (auto t : createPath(graph, s, t, n)) {
        cout << t << " ";
    }
    cout <<"\n";
    for (auto t : createPath(graph, s, t, n)) {
        cout << t << " ";
    }

   /* cout << sum << std::endl;
    for (int i = 0; i < m; i++) {
        int num;
        if (num = edges[i].first->flow) {
            cout << num << "\n";
        } else if (num = edges[i].second->flow) {
            cout << -num << "\n";
        } else {
            cout << 0 << "\n";
        }
    }*/

    return 0;
}
