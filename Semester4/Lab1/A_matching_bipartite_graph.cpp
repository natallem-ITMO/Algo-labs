#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>

#include <set>
//#include "../../../Helper/show_collections.hpp"
using namespace std;

bool dfs(int i, vector<vector<int>> & edges, vector<int> & matching, vector<bool> & visited){
    if (visited[i]) return false;
    visited[i] = true;
    for (int j : edges[i]){
        if (matching[j]==-1 || dfs(matching[j], edges, matching, visited)) {
            matching[j] = i;
            return true;
        }
    }
    return false;
}

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> matching(m + 1, -1);
    vector<vector<int>> edges(n + 1);
    for (int i = 1; i <= n; i++) {
        int x = 0;
        cin >> x;
        vector<int> cur_edges;
        while (x != 0) {
            cur_edges.push_back(x);
            cin >> x;
        }
        edges[i] = cur_edges;
    }
    vector<bool> visited(n+1);
    for (int i = 1; i <= n; i++){
        fill(visited.begin(), visited.end(), false);
        dfs(i,edges,matching, visited);
    }
    int counter = 0;
    for (int i = 1; i <= m ; i++){
        if (matching[i] != -1) counter++;
    }
    cout << counter << "\n";
    for (int i = 1; i <= m; i++){
        if (matching[i] != -1){
            cout << matching[i] << " " << i << "\n";
        }
    }
}