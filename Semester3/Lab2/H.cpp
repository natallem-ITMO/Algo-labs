

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <queue>

using namespace std;

bool do_sort(vector<vector<int>> &edges, vector<int> &cnt, vector<int> &res, int N, queue<int> &q) {
    for (int i = N-1; i >= 0; i--) {
        if (q.empty()) return false;
        int v = q.front();
        q.pop();
        for (int u : edges[v]) {
            cnt[u]--;
            if (cnt[u] == 0) q.push(u);
        }
        res[i]=v;
    }
    return true;
}

bool do_game(vector<vector<int>> & edges, vector<int> & top_sort, int N, int S){
    vector<bool> game(N+1, false);
//    game[top_sort[top_sort.size()-1]] = false;
    for (int v : top_sort){
        for (int u : edges[v]){
            if (game[u]==0){
                game[v]=true;
                break;
            }
        }
    }
    return game[S];
}

int main() {

/*#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif*/
    std::ifstream cin("game.in");
    std::ofstream cout("game.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, S;
    cin >> N >> M>> S;
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
        if (cnt[i + 1]==0) q.push(i+1);
    }
    vector<int> top_sort(N);
    do_sort(edges, cnt, top_sort, N, q);
    if (do_game(edges,top_sort,N, S)){
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
//    cout<<endl<< do_game(edges,top_sort,N)[S];

}

