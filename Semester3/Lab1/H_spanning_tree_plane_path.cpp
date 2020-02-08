//
// Created by natalem on 12.10.2019.
//


#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
long long int n;
vector<vector<long long int>> matrix;

void dfs(long long int v, vector<bool> &visited, vector<vector<long long int>> &edges) {
    visited[v] = true;
    for (long long int i: edges[v]) {
        if (!visited[i])
            dfs(i, visited, edges);
    }
}

bool can(long long int x) {
    vector<vector<long long int>> in_edges(n + 1, vector<long long int>());// ->v[i]
    vector<vector<long long int>> out_edges(n + 1, vector<long long int>());// v[i]->
    for (long long int i = 1; i <= n; i++) {
        for (long long int j = 1; j <= n; j++) {
            if (matrix[i][j] <= x) {
                //i->j
                in_edges[j].push_back(i);
                out_edges[i].push_back(j);
            }
        }
    }
    vector<bool> visited(n + 1, false);
    dfs(1, visited, out_edges);
    for (long long int i = 1; i <= n; i++) {
        if (!visited[i]) return false;
    }
    visited = vector<bool>(n + 1, false);
    dfs(1, visited, in_edges);
    for (long long int i = 1; i <= n; i++) {
        if (!visited[i]) return false;
    }
    return true;
}

long long int bin_search() {
    long long int L = 0;
    long long int R = 2000000000;

    while (L < R) {

        long long int Mid = (L + R) / 2;


        if (can(Mid)) R = Mid; else L = Mid + 1;

    }
    return L;
}

void do_task() {
    std::ifstream cin("avia.in");
    std::ofstream cout("avia.out");

    cin >> n;
    matrix=vector<vector<long long int>>(n+1, vector<long long int>(n+1,0));
  //  vector<vector<long long int>> matr(n + 1, vector<long long int>(n + 1, 0));
    for (long long int i = 1; i < n + 1; i++) {
        for (long long int j = 1; j < n + 1; j++) {
            long long int a;
            cin >> a;
            matrix[i][j] = a;
        }
    }
//    show_collection(matrix);

    cout << bin_search();
}

int main() {
    do_task();
}
