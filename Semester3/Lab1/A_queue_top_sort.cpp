//
// Created by natalem on 10.10.2019.
//

/*
 * Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.

Входные данные
В первой строке входного файла даны два натуральных числа N и M (1 ≤ N ≤ 100 000, 0 ≤ M ≤ 100 000) — количество вершин
 и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел — номерами
 начальной и конечной вершин соответственно.

Выходные данные
Вывести любую топологическую сортировку графа в виде последовательности номеров вершин. Если граф невозможно
топологически отсортировать, вывести -1.

 Пример
входные данные


выходные данные
4 6 3 1 2 5
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <queue>

using namespace std;

bool do_sort(vector<vector<int>> &edges, vector<int> &cnt, vector<int> &res, int N, queue<int> &q) {
    for (int i = 0; i < N; i++) {
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

int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
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
        if (cnt[i + 1]==0) q.push(i+1);
    }
    vector<int> res(N);
    if (do_sort(edges, cnt, res, N, q)) {
        for (int i : res) cout << i << " ";
    } else {
        cout << "-1";
    }
}

