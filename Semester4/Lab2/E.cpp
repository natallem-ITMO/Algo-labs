#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <numeric>
#include <unordered_map>

using namespace std;

struct edge {
    int start;
    int end;
    bool isReversed;
    edge *pair;
    edge *realPair;
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

const int MAX_CAP = INT32_MAX;

int N, M, K, S, T, P, L;
int n, s;
vector<vector<int>> directed_edges;
vector<vector<int>> edges;
vector<vector<edge * >> graph;
unordered_map<string, edge *> edge_by_vertex;

int findShortestPath() {
    queue<int> q;
    q.push(S);
    vector<int> visited(N + 1, -1);
    visited[S] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (auto next : directed_edges[cur]) {
            if (visited[next] == -1) {
                visited[next] = visited[cur] + 1;
                q.push(next);
            }
            if (next == T) {
                return visited[next];
            }
        }
    }
    return -1;
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

int getNormalVertex(int start) {
    int x = start % N;
    if (x == 0) return N;
    return x;
}

int getTimeVertex(int vertex, int time) {
    return vertex + time * N;
}

void createTimeEdges(int time) {
    for (int u = 1; u <= N; u++) {
        for (auto v : edges[u]) {
            edge * u_v = makeEdge(getTimeVertex(u, time), getTimeVertex(v, time + 1), 1);
            swap(u,v);
            edge * v_u = makeEdge(getTimeVertex(u, time), getTimeVertex(v, time + 1), 1);
            swap(u,v);
            u_v ->realPair = v_u;
            v_u ->realPair = u_v;
        }
        int next = u;
        edge * u_u = makeEdge(getTimeVertex(u, time), getTimeVertex(next, time + 1), MAX_CAP);
        u_u->realPair = nullptr;
    }
}

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
    }
    return sum;
}

void merge_vectors(vector<vector<int>> &ships, vector<vector<int>> &new_ships) {
    for (int i = 1; i < ships.size(); i++) {
        for (int ship : new_ships[i]) {
            ships[i].push_back(ship);
        }
    }
}

void check_double_go(){
    for (auto vec_edges : graph){
        for (auto e : vec_edges){
            if (e->isReversed) continue;
            if (e->capacity == MAX_CAP) continue;
            if (e->flow==1 && e->realPair->flow==1) {
                e->decreaseFlow();
                e->realPair->decreaseFlow();
            }
        }
    }
}

void showResult(int time, int maxFlow) {
    check_double_go();
    cout << time + 1 << "\n";
    vector<vector<int>> ships_in_vertex(N + 1, vector<int>());
    vector<int> initialShips(maxFlow);
    iota(initialShips.begin(), initialShips.end(), 1);
    ships_in_vertex[S] = initialShips;
    vector<vector<string>> ans(time + 1, vector<string>());
    for (int day = 0; day <= time; day++) {
        vector<vector<int>> new_ships_in_vertex(N + 1, vector<int>());
        for (int i = 1; i <= N; i++) {
            if (!ships_in_vertex[i].empty()) {
                int cur_day_vertex = getTimeVertex(i, day);
                for (edge *e : graph[cur_day_vertex]) {
                    if (e->flow < 1) continue;
                    if (e->isReversed) continue;
                    e->decreaseFlow();
                    int nextVertex = getNormalVertex(e->end);
                    if (i == nextVertex) continue;
                    int ship = ships_in_vertex[i].back();
                    new_ships_in_vertex[nextVertex].push_back(ship);
                    ships_in_vertex[i].pop_back();
                    ans[day].push_back(to_string(ship) + " " + to_string(nextVertex));
                }
            }
        }
        merge_vectors(ships_in_vertex, new_ships_in_vertex);
        if (maxFlow != K) continue;
        cout << ans[day].size() << "  ";
        for (auto &t : ans[day]) {
            cout << t << " ";
        }
        cout << "\n";
    }
}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
//    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K >> S >> T;
    directed_edges.resize(N + 1, vector<int>());
    edges.resize(N + 1, vector<int>());
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        edges[x].push_back(y);
        if (x != T) {
            directed_edges[x].push_back(y);
        }
        if (x != S) {
            swap(x, y);
            directed_edges[x].push_back(y);
        }
    }

    L = findShortestPath();
    P = L + K;
    n = N * P;
    s = getTimeVertex(S, 0);

    graph.resize(N * (P + 1) + 1, vector<edge *>());
    int sum = 0;
    int newFlow;
    for (int i = 0; i <= M + 2 * K; i++) {
        createTimeEdges(i);
        int t = getTimeVertex(T, i + 1);
        while (newFlow = bfs(s, t)) {
            sum += newFlow;
            if (sum == K) {
                showResult(i, sum);
                return 0;
            }
        }
    }
}
