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

void setDepth(int vertex, vector<vector<int>> & sons,   vector<int> & depth){
   int prevDepth = depth[vertex-1];
   ++prevDepth;
   for (int son : sons[vertex-1]){
       depth[son-1] = prevDepth;
       setDepth(son,sons, depth);
   }
}

int lca(int a,int b, vector<int> & d, vector<vector<int>> & dp, int log_n){
    if (d[a-1] < d[b-1])  swap (a,b);
    if (d[a-1]!=d[b-1]) {
        for (int i = log_n; i >= 0 ; i-- ){
            if ((1 << i) <= d[a-1]-d[b-1]){
                a = dp[a-1][i];
            }
        }
    }
    if (a==b) return a;
    for (int i = log_n; i >= 0 ; i-- ){
        int dpa = dp[a-1][i];
        int dpb = dp[b-1][i];

        if(dp[a-1][i]!=dp[b-1][i]){
            a = dp[a-1][i];
            b = dp[b-1][i];
        }
    }
    return dp[a-1][0];
}

using namespace std;

int main() {
    int n;
    cin >> n;
    int x = find_log_2(n);
    vector<int> sample(x, 0);
    vector<vector<int>> dp(n, vector<int>(x+1, 0));
    vector<vector<int>> sons(n);
    vector<int> depth(n);
    dp[0][0] = 1;

    for (int i = 1; i < n; i++) {
        cin >> dp[i][0];
        sons[dp[i][0]-1].push_back(i+1);
    }
    depth[0] = 0;
    setDepth(1, sons, depth);
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            dp[j][i] = dp[dp[j][i - 1]-1][i - 1];
        }
    }/*
    for (int i = 0; i < n; i++) {
        cout << (i + 1) << ": ";
        for (int j = 0; j < x; j++) {
            if (dp[i][j] != 0) cout << dp[i][j] << " ";
        }
        cout << "\n";
    }*/
//    showMatrix(dp);
//    showMatrix(sons);
//    showVector(depth);
    int m;

    cin >> m;
    for (int i= 0; i < m; i++){
        int a , b;
        cin >> a >>b;
        cout << lca(a,b, depth, dp,x)<<"\n";
    }
  // cout <<  lca(1,1,depth,dp,x)<<"\n";

    return 0;
}