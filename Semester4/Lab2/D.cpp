#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <set>

using namespace std;

const int MAX_CAP = 60000;
int a, b, upper;

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

void dfs(int v, vector<bool> &visited, vector<vector<edge *>> &graph) {
    visited[v] = true;
    for (edge *child : graph[v]) {
        if (child->getC() == 0) continue;
        int nextVertex = child->end;
        if (!visited[nextVertex]) dfs(nextVertex, visited, graph);
    }
}

int getNum(int y, int x) {
    return x + y * b;
}

int getCut(vector<vector<edge *>> &graph, int start, int n, vector<string> &m) {
    vector<bool> visited(n + 1, false);
    set<int> result;
    dfs(start, visited, graph);
    int counter = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (visited[getNum(i, j)] && !visited[getNum(i, j) + upper]) {
                counter++;
                m[i][j] = '+';
            }
        }
    }
    return counter;
}

bool canEdge(char start, char end) {
    return (start != '#' && end != '#');
}


bool createA(char start, char end, int numStart, int numEnd, vector<vector<edge *>> &graph) {
    if (start == 'A') {
        makeEdge(upper + numStart, numEnd, MAX_CAP, graph);
        return true;
    }
    if (end == 'A') {
        makeEdge(upper + numEnd, numStart, MAX_CAP, graph);
        return true;
    }
    return false;
}

bool createB(char start, char end, int numStart, int numEnd, vector<vector<edge *>> &graph) {
    if (end == 'B') {
        makeEdge(upper + numStart, numEnd, MAX_CAP, graph);
        return true;
    }
    if (start == 'B') {
        makeEdge(upper + numEnd, numStart, MAX_CAP, graph);
        return true;
    }
    return false;
}


void fall() {
    vector<int> n;
    n[9] = 342;
}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> a >> b;
    int n = a * b * 2;
    upper = a * b;

    vector<vector<edge *>> graph(n + 1, vector<edge *>());
    vector<string> m(a);

    for (int i = 0; i < a; i++) {
        cin >> m[i];
    }

    int startIndex = -1;
    int endIndex = -1;

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (m[i][j] == 'A') startIndex = getNum(i, j);
        }
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (m[i][j] == 'B') endIndex = getNum(i, j);
        }
    }
    if (startIndex == -1 || endIndex == -1) {
        fall();
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            char start = m[i][j];
            if (start == '#') continue;
            int startNum = getNum(i, j);
            int capacity = (start != '.') ? MAX_CAP : 1;
            makeEdge(startNum, startNum + upper, capacity, graph);
        }
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b - 1; j++) {
            char start = m[i][j];
            char end = m[i][j + 1];
            if (canEdge(start, end)) {
                int startNum = getNum(i, j);
                int endNum = getNum(i, j + 1);
                if (createA(start, end, startNum, endNum, graph)) {
                    continue;
                }
                if (createB(start, end, startNum, endNum, graph)) {
                    continue;
                }
                makeEdge(upper + startNum, endNum, MAX_CAP, graph);
                makeEdge(upper + endNum, startNum, MAX_CAP, graph);
            }
        }
    }
    for (int i = 0; i < a - 1; i++) {
        for (int j = 0; j < b; j++) {
            char start = m[i][j];
            char end = m[i + 1][j];
            if (canEdge(start, end)) {
                int startNum = getNum(i, j);
                int endNum = getNum(i + 1, j);
                if (createA(start, end, startNum, endNum, graph)) {
                    continue;
                }
                if (createB(start, end, startNum, endNum, graph)) {
                    continue;
                }
                makeEdge(upper + startNum, endNum, MAX_CAP, graph);
                makeEdge(upper + endNum, startNum, MAX_CAP, graph);
            }
        }
    }


    int sum = 0;
    int num;
    while (num = bfs(graph, startIndex, endIndex, n)) {
        sum += num;
        if (sum >= MAX_CAP) {
            cout << -1;
            return 0;
        }
    }

    int res = getCut(graph, startIndex, n, m);
    cout << res << '\n';
    for (auto t : m) {
        cout << t << '\n';
    }
    return 0;
}
