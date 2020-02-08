
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
/*
#define _CRT_SECURE_NO_WARNINGS
*/
//#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <deque>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <string>
#include <set>
#include <queue>
#include <iomanip>
#include <bitset>
#include <cassert>
#include <random>
/*
// some useful typedef
// you can write
// ll a; and it is long long a;
typedef long double ld;
typedef int64_t ll;
typedef uint64_t ull;
typedef int32_t int32;
*/
using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

// uncomment this for more memory. Number is memory - byte
//#pragma comment (linker, "/STACK:5000000000")

//////////////////////////////////////////////////////////////////
// SYSTEM STARTS

//////////////////////////////////////////////////////////////////
// UTILS
vector<int> level;
vector<int> father;
vector<vector<int>> edges;
int n;
/////////////////////////////////////////////////////////////////
// MAIN

int center_size(int v, int size, int &center, int p = -1) {
    int sum = 1;
    for (int x : edges[v])
        if (level[x] == -1 && x != p) {
            sum += center_size(x, size, center, v);
        }
    if (center == -1 && (2 * sum >= size || p == -1))
        center = v;
    return sum;
}

void decompose(int v, int size, int depth, int last) {
//    vector<int> * level_ = & level;
//    vector<int> * parent_ = &father;
//    vector<vector<int>> * graph_ = &edges;
//    int * n_ = &n;
    int center = -1;
    center_size(v, size, center);
    level[center] = depth;
    father[center] = last;
    for (int x : edges[center]) {
        if (level[x] == -1)
            decompose(x, size / 2, depth + 1, center);
    }
}

int main() {
 /*   // begin of my useless prog
#ifdef _DEBUG
    // here files from debug
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#else
    // here files for testing system
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif*/
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    vector<int> s;
    for (int i = 0; i <= n; i++) {
        level.push_back(-1);
        father.push_back(0);
        edges.push_back(s);
    }
    for (int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    decompose(1, n, 0, 0);
    for (int i = 1; i <= n; i++){
        cout << father[i] << " ";
    }
//    cout << endl;
//    for (int i = 1; i <= n; i++){
//        cout << i << " ";
//    }

    return 0;
}
