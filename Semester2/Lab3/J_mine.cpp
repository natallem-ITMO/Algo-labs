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

//#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");
int n;
vector<bool> is_centroid;
vector<vector<int>> sons;
vector<int> father;
vector<int> size_tree;
vector<bool> visited;

void get_size(int vertex){
    visited[vertex] = true;
    size_tree[vertex] = 1;
    for (int x : sons[vertex]){
        if (!is_centroid[x] && !visited[x]){
            get_size(x);
            size_tree[vertex] += size_tree[x];
        }
    }
}
int find_centroid(int vertex, int size_of_tree){
    visited[vertex] = true;
    int max_son = -1;
    for (int x : sons[vertex]){
        if (!is_centroid[x] && !visited[x]){
            if (size_tree[x] > (size_of_tree/2)){
                if (max_son == -1 || size_tree[max_son] < size_tree[x]) max_son = x;
            }
        }
    }
    if (max_son!=-1) return find_centroid(max_son, size_of_tree);
    return vertex;
}

int get_centroid_from_root(int vertex){
    for (int i = 0; i <=n ; i++){
        visited[i] = false;
        size_tree[i] = 1;
    }
    get_size(vertex);//vertex not centroid
    for (int i = 0; i <=n ; i++){
        visited[i] = false;
    }
    int centroid = find_centroid(vertex, size_tree[vertex]);
    is_centroid[centroid] = true;
    return centroid;
}

int centroid_decompose(int vertex){
    int cur_centoid = get_centroid_from_root(vertex);
    for (int x : sons[cur_centoid]){
        if (!is_centroid[x]){
            int child = centroid_decompose(x);
            father[child] = cur_centoid;
        }
    }
    return cur_centoid;
}

int main123(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    vector<int> sample;
    for (int i = 0; i <=n; i++){
        is_centroid.push_back(false);
        sons.push_back(sample);
        father.push_back(0);
        visited.push_back(false);
        size_tree.push_back(1);
    }
    for (int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        sons[u].push_back(v);
        sons[v].push_back(u);
    }
    //int res = get_centroid_from_root(1, sons);
    centroid_decompose(1);
    for (int i = 1; i <= n; i ++){
        cout << father[i] << " ";
    }
}*/
