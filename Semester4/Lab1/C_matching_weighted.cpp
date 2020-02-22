#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
//#include "../../../Helper/show_collections.hpp"

bool debug = false;

bool showMatchingBool = false;
using namespace std;

void showMatching(vector<int> &t, int i) {
    printf("matching %d : \n", i);
    for (int i = 0; i < t.size(); i++) {
        printf("%d -> %d\n", i, t.at(i));
    }
}

bool dfs(int i, vector<unordered_map<int, int>> &edges, vector<int> &matching, vector<bool> &visited) {
    if (visited.at(i)) return false;
    visited.at(i) = true;
    for (auto p : edges.at(i)) {
        int j = p.first;
        if (matching.at(j) == -1 || dfs(matching.at(j), edges, matching, visited)) {
            matching.at(j) = i;
            return true;
        }
    }
    return false;
}

vector<int> find_maxA_matching(vector<unordered_map<int, int>> &edges, int n_sizeA, int m_sizeB,
                               vector<int> &order) {   // A | B //starts with 1, n_sizeA is 1..n_sizeA
    //return max matching to B
    //m_sizeB is for B. n_sizeA is for A
    vector<int> matching(m_sizeB + 1, -1);
    vector<bool> visited(n_sizeA + 1);
    for (int i = 1; i <= n_sizeA; i++) {
        fill(visited.begin(), visited.end(), false);
        dfs(order.at(i), edges, matching, visited);
        if (showMatchingBool) showMatching(matching, i);
    }
    return matching;
}

void
dfsPath(int i, int prev, vector<unordered_set<int>> &edges1matching, vector<unordered_set<int>> &edges2matching,
        vector<int> &curPath, vector<bool> &visited1, vector<bool> &visited2) {
    curPath.push_back(i);
    visited1.at(i) = true;
    int next = -1;
    for (auto t : edges1matching.at(i)) {
        if (t != prev) next = t;
    }
    if (next == -1) return;
    dfsPath(next, i, edges2matching, edges1matching, curPath, visited2, visited1);
}

void dfsCycles(int i, vector<unordered_set<int>> &edgesAmatching, vector<unordered_set<int>> &edgesBmatching,
               vector<bool> &visitedA, vector<bool> &visitedB) {
    if (visitedA.at(i)) return;
    visitedA.at(i) = true;
    int b = *edgesAmatching.at(i).begin();
    visitedB.at(b) = true;
    auto itrb = edgesBmatching.at(b).begin();
    if ((*itrb) == i) itrb++;
    int next = *itrb;
    edgesBmatching.at(b).erase(next);
    edgesAmatching.at(next).erase(b);
    dfsCycles(next, edgesAmatching, edgesBmatching, visitedA, visitedB);
}

void processPaths(vector<unordered_set<int>> &edgesAmatching, vector<unordered_set<int>> &edgesBmatching,
                  vector<bool> &visitedA, vector<bool> &visitedB, vector<int> &wA) {
    for (int i = 1; i < edgesAmatching.size(); i++) {
        if (!visitedA.at(i)) {
            if (edgesAmatching.at(i).size() == 1) {
                vector<int> path;
                dfsPath(i, -10, edgesAmatching, edgesBmatching, path, visitedA, visitedB);
                if (path.size() % 2 == 0) {
                    for (int i = 1; i < path.size() - 1; i += 2) {
                        edgesBmatching.at(path.at(i)).erase(path.at(i + 1));
                        edgesAmatching.at(path.at(i + 1)).erase(path.at(i));
                    }
                } else {
                    if (wA.at(path.at(0)) > wA.at(*(--path.end()))) {
                        for (int i = 1; i < path.size(); i += 2) {
                            edgesBmatching.at(path.at(i)).erase(path.at(i + 1));
                            edgesAmatching.at(path.at(i + 1)).erase(path.at(i));
                        }
                    } else {
                        for (int i = 0; i < path.size() - 1; i += 2) {
                            edgesAmatching.at(path.at(i)).erase(path.at(i + 1));
                            edgesBmatching.at(path.at(i + 1)).erase(path.at(i));
                        }
                    }
                }
            }
        }
    }
}

int main() {
#ifdef MY_DEBUG
    string filename = "a";
    std::ifstream cin(filename + ".in");
    std::ofstream cout(filename + ".out");
    debug = true;
    showMatchingBool = false;
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, e;
    cin >> n >> m >> e;
    vector<unordered_map<int, int>> edgesA(n + 1, unordered_map<int, int>());
    vector<unordered_map<int, int>> edgesB(m + 1, unordered_map<int, int>());
    vector<unordered_set<int>> edgesAmatching(n + 1, unordered_set<int>());
    vector<unordered_set<int>> edgesBmatching(m + 1, unordered_set<int>());
    vector<int> wA(n + 1);
    vector<int> wB(m + 1);
    vector<pair<int, int>> ordera(n + 1);
    ordera[0] = {1000000000, 0};
    vector<pair<int, int>> orderb(m + 1);
    orderb[0] = {1000000000, 0};
    vector<int> orderA(n + 1);
    vector<int> orderB(m + 1);
    //заполняем веса
    for (int i = 1; i <= n; i++) {
        cin >> wA.at(i);
    }
    for (int i = 1; i <= m; i++) {
        cin >> wB.at(i);
    }
    for (int i = 1; i <= n; i++) {
        ordera[i] = {wA[i], i};
    }
    for (int i = 1; i <= m; i++) {
        orderb[i] = {wB[i], i};
    }
    //заполняем ребра
    for (int i = 1; i <= e; i++) {
        int a, b;
        cin >> a >> b;
        edgesA.at(a).insert({b, i});
        edgesB.at(b).insert({a, i});
    }
    sort(ordera.begin(), ordera.end());
    sort(orderb.begin(), orderb.end());
    for (int i = ordera.size() - 1; i >= 0; i--) {
        orderA[ordera.size() - 1 - i] = ordera[i].second;
    }
    for (int i = orderb.size() - 1; i >= 0; i--) {
        orderB[orderb.size() - 1 - i] = orderb[i].second;
    }
    vector<int> matchingA = find_maxA_matching(edgesA, n, m, orderA);
    vector<int> matchingB = find_maxA_matching(edgesB, m, n, orderB);

    for (int i = 1; i < matchingA.size(); i++) {
        if (matchingA.at(i) != -1) {
            edgesBmatching.at(i).insert(matchingA.at(i));
            edgesAmatching.at(matchingA.at(i)).insert(i);
        }
    }
    for (int i = 1; i < matchingB.size(); i++) {
        if (matchingB.at(i) != -1) {
            edgesAmatching.at(i).insert(matchingB.at(i));
            edgesBmatching.at(matchingB.at(i)).insert(i);
        }
    }
    vector<bool> visitedA(n + 1, false);
    vector<bool> visitedB(m + 1, false);

    //находим пути в левой доле
    processPaths(edgesAmatching, edgesBmatching, visitedA, visitedB, wA);

    //находим пути в правой доле
    processPaths(edgesBmatching, edgesAmatching, visitedB, visitedA, wB);

    //остались циклы
    for (int i = 1; i < edgesAmatching.size(); i++) {
        if (edgesAmatching.at(i).size() == 2) {
            dfsCycles(i, edgesAmatching, edgesBmatching, visitedA, visitedB);
        }
    }
    vector<int> res;
    int sum = 0;
    for (int i = 1; i < edgesAmatching.size(); i++) {
        if (edgesAmatching.at(i).size() == 1) {
            res.push_back(edgesA.at(i).at(*edgesAmatching.at(i).begin()));
            sum += wA.at(i) + wB.at(*edgesAmatching.at(i).begin());
        }
    }
    cout << sum << "\n" << res.size() << "\n";
    for (int re : res) {
        cout << re << " ";
    }


    return 0;
}



