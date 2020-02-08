

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <fstream>
#include <queue>

using namespace std;

bool do_sort(vector<vector<int>> &edges, vector<int> &cnt, vector<int> &res, int N, queue<int> &q) {
    for (int i = N - 1; i >= 0; i--) {
        if (q.empty()) return false;
        int v = q.front();
        q.pop();
        for (int u : edges[v]) {
            cnt[u]--;
            if (cnt[u] == 0) q.push(u);
        }
        res[i] = v;
    }
    return true;
}

vector<int> grandi(vector<vector<int>> &edges, vector<int> &top_sort, int N) {
    vector<int> grandi(N + 1);
    for (auto v : top_sort) {
        set<int> grandies;
        for (int u : edges[v]) {
            grandies.insert(grandi[u]);
        }
        grandi[v] = -1;
        int need = 0;
        for (int w : grandies) {
            if (need != w) {
                grandi[v] = need;
                break;
            }
            need++;
        }
        if (grandi[v] == -1) grandi[v] = need;
    }
    return grandi;
}

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, S;
    cin >> N >> M;
    vector<vector<int>> edges(N + 1, vector<int>());
    vector<int> cnt(N + 1, 0);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        ++cnt[v];
        edges[u].emplace_back(v);
    }
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (cnt[i + 1] == 0) q.push(i + 1);
    }
    vector<int> top_sort(N);
    do_sort(edges, cnt, top_sort, N, q);
    /*for (int i : top_sort) {
        cout << i << " ";
    }*/
    auto grand = grandi(edges, top_sort, N);
    for (int i = 1; i < grand.size(); i++) {
        cout << grand[i] << "\n";
    }
//    cout<<endl<< grandi(edges,top_sort,N)[S];

}

