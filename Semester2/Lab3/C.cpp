//#include <iostream>
#include <fstream>
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
const int MAX = 100000000;

std::ifstream cin("minonpath.in");
std::ofstream cout("minonpath.out");

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

void setDepth(int vertex, vector<vector<int>> &sons, vector<int> &depth) {
    int prevDepth = depth[vertex - 1];
    ++prevDepth;
    for (int son : sons[vertex - 1]) {
        depth[son - 1] = prevDepth;
        setDepth(son, sons, depth);
    }
}

int lcaMin(int a, int b, vector<int> &d, vector<vector<int>> &dp, vector<vector<int>> &dpc, int log_n) {
    int res = MAX;
    if (d[a - 1] < d[b - 1]) swap(a, b);//a ниже b
    if (d[a - 1] != d[b - 1]) {
        for (int i = log_n; i >= 0; i--) {
            if ((1 << i) <= d[a - 1] - d[b - 1]) {
                res = min(res, dpc[a - 1][i]);
                a = dp[a - 1][i];
            }
        }
    }
    if (a == b) return res;
    for (int i = log_n; i >= 0; i--) {
        int dpa = dp[a - 1][i];
        int dpb = dp[b - 1][i];

        if (dp[a - 1][i] != dp[b - 1][i]) {

            res = min(res, dpc[a - 1][i]);
            a = dp[a - 1][i];

            res = min(res, dpc[b - 1][i]);
            b = dp[b - 1][i];
        }
    }
    res = min(res, dpc[a - 1][0]);
    res = min(res, dpc[b - 1][0]);
    return res;
}

using namespace std;

int main() {
    int n;
    cin >> n;
    int x = find_log_2(n);
    vector<vector<int>> dp(n, vector<int>(x + 1, 0));
    vector<vector<int>> dpc(n, vector<int>(x + 1, MAX));
    vector<vector<int>> sons(n);
    vector<int> depth(n);
    dp[0][0] = 1;

    for (int i = 1; i < n; i++) {
        cin >> dp[i][0] >> dpc[i][0];
        sons[dp[i][0] - 1].push_back(i + 1);
    }
    //   showMatrix(dpc);
    depth[0] = 0;
    setDepth(1, sons, depth);
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            dp[j][i] = dp[dp[j][i - 1] - 1][i - 1];
            dpc[j][i] = min(dpc[j][i - 1], dpc[dp[j][i-1]-1][i - 1]);
        }
    }
  //   showMatrix(dpc);
//    showMatrix(sons);
//    showVector(depth);
    int m;

    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cout << lcaMin(a, b, depth, dp, dpc, x) << "\n";
    }
    // cout <<  lca(1,1,depth,dp,x)<<"\n";

    return 0;
}