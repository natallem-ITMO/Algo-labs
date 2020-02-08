#include <iostream>
//#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

int find_log_2(int x) {//минимальное большее либо равное x
    int i = 0;
    int xi = 1;
    while (true) {
        if (xi >= x) break;
        xi <<= 1;
        i++;
    }
    return i;
}

static void showVector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void showSet(set<int> &vec) {
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;
}

static void showSet(unordered_set
                            <int> &set) {
    unordered_set<int>::iterator itr;
    for (itr = set.begin(); itr != set.end(); itr++) {
        cout << (*itr) << " ";
    }
    cout << endl;
}

static void showMatrix(vector<vector<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showVector(m[i]);
    }
    cout << endl;
}

static void showMatrixSet(vector<set<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showSet(m[i]);
    }
    cout << endl;
}



int lca(int a, int b, vector<int> &d, vector<vector<int>> &dp, int log_n) {
    if (d[a] < d[b]) swap(a, b);
    if (d[a] != d[b ]) {
        for (int i = log_n; i >= 0; i--) {
            if ((1 << i) <= d[a] - d[b]) {
                a = dp[a][i];
            }
        }
    }
    if (a == b) return a;
    for (int i = log_n; i >= 0; i--) {
        if (dp[a][i] != dp[b][i]) {
            a = dp[a][i];
            b = dp[b][i];
        }
    }
    return dp[a][0];
}

void dfs(int vertex, int prev_vertex, vector<set<int>> &connect, vector<int> &depth, vector<vector<int>> &dp) {
    int prevDepth = depth[vertex];
    ++prevDepth;
    connect[vertex].erase(prev_vertex);
    for (int son : connect[vertex]) {
        depth[son] = prevDepth;
        dp[son][0] = vertex;
        dfs(son, vertex, connect, depth, dp);
    }
}
void dfs2(int vertex,int & ans, vector<set<int>> & connect, vector<int> & mark){
    for (int i : connect[vertex]){
        dfs2(i, ans,connect, mark);
        mark[vertex] += mark[i];
    }
    if (mark[vertex]==0 && vertex != 1) ans++;
}

using namespace std;

int main() {
    int n;
    cin >> n;
    int log_n = find_log_2(n);
    vector<int> sample(log_n, 0);
    vector<vector<int>> dp(n + 1, vector<int>(log_n + 1, 0));
    vector<set<int>> connect(n + 1);
    vector<int> depth(n + 1);
    vector<int> mark(n+1);
    dp[1][0] = 1;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        connect[x].insert(y);
        connect[y].insert(x);
    }
    depth[1] = 0;
    dfs(1, -1, connect, depth, dp);

    for (int i = 1; i <= log_n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
        }
    }
//    showMatrix(dp);
//    showVector(depth);
//    showMatrixSet(connect);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        int lca_ = lca(x, y, depth, dp, log_n);
        mark[lca_] -= 2;
        mark[x] ++;
        mark[y] ++;
    }
//    showVector(mark);
    int ans = 0;
    int & ptr = ans;
    dfs2(1, ptr, connect, mark);
    cout << ans;

    return 0;
}