#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <numeric>
#include <algorithm>
#include <unordered_map>

using namespace std;

int n, N;

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

    void decreaseFlow() {
        --flow;
        ++pair->flow;
    }

    void cleanEdge() {
        flow = 0;
        pair->flow = 0;
    }

    edge(int start, int end, bool isReversed) : start(start), end(end), isReversed(isReversed), capacity(0),
                                                flow(0) {}

};

vector<vector<edge * >> graph;

int bfs(int start, int end) {
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
        vector<edge *> path;
        while (parent != start) {
            path.push_back(incomeEdge[parent]);
            incomeEdge[parent]->flow += sum;
            incomeEdge[parent]->pair->flow -= sum;
            parent = incomeEdge[parent]->start;
        }
//        reverse(path.begin(), path.end());
//        cout << "path max = " << sum << "\n";
//        for (auto t : path) {
//            cout << t->start << "<->" << t->end << " ";
//        }
//        cout << "\n";


    }
    return sum;
}


edge *makeEdge(int start, int end, int capacity) {
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

vector<vector<edge * >> &getGraph() {
    return graph;
}

int maxFlow(int s, int t) {
    int sum = 0;
    int num;
    while (num = bfs(s, t)) {
        sum += num;
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
    cin >> N;
    vector<int> total_points(N + 1, 0);
    vector<pair<int, int>> games;
    vector<string> table(N);
    for (int i = 0; i < N; i++) {
        cin >> table[i];
        for (int j = 0; j < i; j++) {
            char r = table[i][j];
            switch (r) {
                case 'W':
                    total_points[i] -= 3;
                    break;
                case 'w':
                    total_points[i] -= 2;
                    total_points[j] -= 1;
                    break;
                case 'L':
                    total_points[j] -= 3;
                    break;
                case 'l':
                    total_points[j] -= 2;
                    total_points[i] -= 1;
                    break;
                case '.':
                    games.emplace_back(i + 1, j + 1);
                    break;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        total_points[i] += x;
    }
    //   v[1]            v[n+1]
    // 0 | 1 2 3 4 ... n | 1 2 3 4 5 6 7 8
    // start  commands       games
    graph.resize(1 + 1 + games.size() + N, vector<edge *>());

    int S = 0;
    int T = graph.size() - 1;
    n = graph.size();
    for (int i = 1; i <= games.size(); i++) {
        int game_v = i + N;
        makeEdge(0, game_v, 3);
        auto[u, v] = games[i - 1];
        makeEdge(game_v, u, 3);
        makeEdge(game_v, v, 3);
    }
    for (int i = 0; i < N; i++) {
        makeEdge(i + 1, T, total_points[i]);
    }
    auto gr = getGraph();
    int res = maxFlow(S, T);
    vector<char> result = {'L', 'l', 'w', 'W'};
    for (int i = 1 + N; i < T; i++) {
        vector<edge *> normal_edges;
        for (auto e : graph[i]) {
            if (!e->isReversed) normal_edges.push_back(e);
        }
        auto[p1, p2] = make_pair(normal_edges[0]->end, normal_edges[1]->end);
        auto[f1, f2] = make_pair(normal_edges[0]->flow, normal_edges[1]->flow);
        table[p1 - 1][p2 - 1] = result[f1];
        table[p2 - 1][p1 - 1] = result[f2];
    }
    for (auto & str : table) {
        cout << str << "\n";
    }
}