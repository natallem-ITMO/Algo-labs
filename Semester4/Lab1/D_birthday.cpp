#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <fstream>
#include <unordered_set>
#include <cmath>

bool debug = false;

using namespace std;

void showMatching(vector<int> &t, int i) {
    printf("matching %d : \n", i);
    for (int i = 0; i < t.size(); i++) {
        printf("%d -> %d\n", i, t[i]);
    }
}

bool dfs(int i, vector<vector<int>> &edges, vector<int> &matching, vector<bool> &visited) {
    if (visited[i]) return false;
    visited[i] = true;
    for (int j : edges[i]) {
        if (matching[j] == -1 || dfs(matching[j], edges, matching, visited)) {
            matching[j] = i;
            return true;
        }
    }
    return false;
}

vector<int> find_matching(vector<vector<int>> &edges, int n, int m) {   // A | B //starts with 1, n is 1..n
    //return max matching to B
    //m is for B. n is for A
    vector<int> matching(m + 1, -1);
    vector<bool> visited(n + 1);
    for (int i = 1; i <= n; i++) {
        fill(visited.begin(), visited.end(), false);
        dfs(i, edges, matching, visited);
        if (debug) showMatching(matching, i);
    }
    return matching;
}

void freeDFS(int i, vector<vector<int>> &edges, vector<int> &matching, vector<bool> &visitedA, vector<bool> &visitedB) {
    if (visitedA[i]) return;
    visitedA[i] = true;
    for (int j : edges[i]) {
        if (!visitedB[j]) {
            visitedB[j] = true;
            if (matching[j] != -1) {
                freeDFS(matching[j], edges, matching, visitedA, visitedB);
            }
        }
    }
}

void solve(ifstream & cin, ofstream & cout) {


    int m, w;
    cin >> m >> w;
    unordered_set<int> women(w);
    for (int i = 1; i <= w; i++) {
        women.insert(i);
    }
    vector<vector<int>> edges(m + 1, vector<int>());

    for (int i = 1; i <= m; i++) {
        unordered_set<int> curWomen = women;
        int numW;
        cin >> numW;
        while (numW != 0) {
            curWomen.erase(numW);
            cin >> numW;
        }
        for (auto t : curWomen) {
            edges[i].push_back(t);
        }
    }

    auto Bmatching = find_matching(edges, m, w);

    vector<int> Amatching(m + 1, -1);
    for (int i = 1; i < Bmatching.size(); i++) {
        if (Bmatching[i] != -1) {
            Amatching[Bmatching[i]] = i;
        }
    }
    vector<bool> visitedA(m + 1, false);
    vector<bool> visitedB(w + 1, false);
    for (int i = 1; i < Amatching.size(); i++) {
        if (Amatching[i] == -1) {
            freeDFS(i, edges, Bmatching, visitedA, visitedB);
        }
    }
    vector<int> invitedW;
    vector<int> invitedM;
    for (int i = 1; i <= w; i++) {
        if (!visitedB[i]) {
            invitedW.push_back(i);
        }
    }

    for (int i = 1; i <= m; i++) {
        if (visitedA[i]) {
            invitedM.push_back(i);
        }
    }

    cout << invitedM.size() + invitedW.size() << "\n";
    cout << invitedM.size() << " " << invitedW.size() << "\n";
    for (auto i : invitedM) {
        cout << i << " ";
    }
    cout << "\n";
    for (auto i : invitedW) {
        cout << i << " ";
    }
    cout << "\n\n";
}

int main() {
    string filename = "birthday";
#ifdef MY_DEBUG
    filename = "a";
    debug = true;
#endif
    std::ifstream cin(filename + ".in");
    std::ofstream cout(filename + ".out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);//    std::ifstream cin(filename + ".in");
//    std::ofstream cout(filename + ".out");
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        solve(cin, cout);
    }

    return 0;
}



