//
// Created by natalem on 27.10.2019.
//

/*
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <climits>

//#include "../../../Helper/show_collections.hpp"
using namespace std;
//unsigned long long int MAX = ULLONG_MAX;
int MAX = 10000*1000;

struct edge{
    int a, b, w;
};

const int INF = 1000000000;

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin  >> n;
 //   vector<vector<pair<int,int>>> input_edges(n+1, vector<pair<int,int>>());
    vector<edge> e;
//    vector<vector<int>> d(n + 1, vector<int>(n + 1));
//    vector<vector<int>> p(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++){
//        d[i + 1][0]=0;
//        p[i+1][0]=-1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            if (a == 100000) continue;//todo  if (a==100000) continue;
            e.push_back(edge{i, j, a});
        }
    }
    vector<int> d (n, MAX);
    vector<int> p (n, -1);
    int x;
    for (int i=0; i<n; ++i) {
        x = -1;
        for (int j=0; j < e.size(); ++j)
            if (d[e[j].b] > d[e[j].a] + e[j].w) {
                d[e[j].b] = max (-INF, d[e[j].a] + e[j].w);
                p[e[j].b] = e[j].a;
                x = e[j].b;
            }
    }

    if (x == -1)
        cout << "NO";
    else {
        int y = x;
        for (int i=0; i<n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur=y; ; cur=p[cur]) {
            if (cur == y && path.size() > 1)  break;
            path.push_back (cur);
        }
        reverse (path.begin(), path.end());
        cout << "YES\n"<< path.size() << "\n";
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i] << ' ';
    }

    /*
    for (int k = 0; k < n; k++){
        for (int v=1; v <= n; v++){
            d[v][k+1]=d[v][k];
            p[v][k+1]=p[v][k];
            for (auto pair : input_edges[v]){
                int u = pair.first;
                int w = pair.second;
                if (d[v][k+1] > d[u][k]+w){
                    d[v][k+1] = d[u][k]+w;
                    p[v][k+1]=u;
                }
            }
        }
    }

   // show_collection(d);
//    show_collection(p);
    bool contain = false;
    for (int i = 1; i <=n ; i++){
        if (d[i][n] != d[i][n-1]) {
            contain = true;
            break;
        }
    }
    if (contain){
        cout << "YES\n";
        for (int i = 1; i <=n ; i++){
            if (d[i][n] != d[i][n-1]) {
                vector<int> cycle;
                cycle.push_back(i);
                int prev = p[i][n];
                int j = n-1;
                while(prev!=cycle[0] && prev!=-1){
                    cycle.push_back(prev);
                    prev=p[prev][j--];
                }
                cout << cycle.size()<<"\n";
                for (int l : cycle){
                    cout << l << " ";
                }
                break;
            }
        }
    } else {
        cout << "NO";
    }

*/



}