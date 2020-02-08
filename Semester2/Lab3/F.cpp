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
    if (d[a] != d[b]) {
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

void dfs(int vertex, int & cur_time, vector<int> & timer, vector<int> & timer_reverse, vector<vector<int>> &sons) {
   cur_time++;
   timer[vertex] = cur_time;
   timer_reverse[cur_time] = vertex;
   for (int son : sons[vertex]){
       dfs(son, cur_time, timer, timer_reverse,sons);
   }
}
void depth_(int vertex, vector<vector<int>> & sons, vector<int> &depth){
    int prevDepth = depth[vertex];
    ++prevDepth;
    for (int son : sons[vertex]){
        depth[son] = prevDepth;
        depth_(son,sons, depth);
    }
}

using namespace std;

int main() {


    int n;
    scanf("%d", &n);
    int log_n = find_log_2(n);
    vector<int> sample(log_n, 0);
    vector<vector<int>> dp(n + 1, vector<int>(log_n + 1, 0));
    vector<int> timer(n + 1);
    vector<int> timer_reverse(n + 1);
    vector<vector<int>> sons(n + 1);

    // vector<set<int>> connect(n + 1);
    vector<int> depth(n + 1);
    //  vector<int> mark(n+1);
    int root = -1;
    for (int i = 1; i <= n; i++) {
        int parent;
        scanf("%d", &parent);
        if (parent == -1) {
            root = i;
            dp[i][0] = i;
        } else{
            dp[i][0] = parent;
            sons[parent].push_back(i);
        }
    }
    depth[root] = 0;
    depth_(root, sons, depth);
    int time_ = 0;
    dfs(root, time_, timer, timer_reverse, sons);
    for (int i = 1; i <= log_n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
        }
    }
//    showMatrix(dp);
//    showVector(depth);
//    showMatrix(sons);
//    showVector(timer);
    int m;
    scanf("%d", &m);
    for (int i = 0 ; i < m; i++){
       int amount;
        scanf("%d", &amount);
       vector<int> group;
       for (int j = 0; j < amount; j++){
           int ver;
           scanf("%d", &ver);
           group.push_back(timer[ver]);
       }
       sort(group.begin(), group.end());
       long long int ans = depth[timer_reverse[group[0]]]+1;
       for (int j = 1; j < group.size(); j ++){
           int cur_timer_vertex = group[j];
           int prev_timer_vertex= group[j-1];
           int cur_vertex = timer_reverse[cur_timer_vertex];
           int prev_vertex = timer_reverse[prev_timer_vertex];
           ans+=depth[cur_vertex]+1;
           int lca_;
           lca_ = lca(cur_vertex, prev_vertex,depth, dp, log_n);
           ans-=(depth[lca_] + 1);
       }
       printf("%d\n", ans);
    }

    return 0;
}