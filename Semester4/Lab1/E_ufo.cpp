#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>

bool debug = false;

double v;


using namespace std;


inline int parseTime(string &s) {
    int h = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    return 60 * h + m;
}

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

vector<int> find_matching(vector<vector<int>> &edges, int n, int m) {   // A | B
    //return max matching to B
    //m is for B. n is for A
    vector<int> matching(m, -1);
    vector<bool> visited(n);
    for (int i = 0; i < n; i++) {
        fill(visited.begin(), visited.end(), false);
        dfs(i, edges, matching, visited);
        if (debug) showMatching(matching, i);
    }
    return matching;
}

inline long long sqr(int abs) {
    return abs * abs;
}

double calcDist(const pair<int, int> &a, const pair<int, int> &b) {
    return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

bool can_arrive(pair<int, pair<int, int>> &start, pair<int, pair<int, int>> &end) {
    double distance = calcDist(start.second, end.second);
    int diffTime = end.first - start.first;
    if (diffTime < 0) return false;
    return (diffTime * v >= distance);
}

int main() {
    string filename = "ufo";

#ifdef MY_DEBUG
    filename = "a";
    debug = true;
#endif
    std::ifstream cin(filename + ".in");
    std::ofstream cout(filename + ".out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, v1;
    cin >> n >> v1;
    v = (double) v1 / 60;
    vector<pair<int, pair<int, int>>> visits(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int x, y;
        cin >> x >> y;
        visits[i] = {parseTime(s), {x, y}};
    }

    vector<vector<int>> edges(n);
    for (int i = 0; i < visits.size(); i++) {
        for (int j = 0; j < visits.size(); j++) {
            if (i == j) continue;
            if (can_arrive(visits[i], visits[j])) {
                edges[i].push_back(j);
            }
        }
    }
    auto t = find_matching(edges, n, n);

    int ans = 0;

    for (int i : t) {
        if (i == -1) ++ans;
    }
    cout << ans;

    return 0;
}



