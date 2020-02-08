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

using namespace std;

template<class T>
bool found(const unordered_set<T> &set, T t) {
    return set.find(t) != set.end();
}

void top_sort(int v, vector<vector<int>> &edges, vector<int> &mark, unordered_set<int> &cur_vertex_in_sort,
              vector<int> &result) {
    cur_vertex_in_sort.insert(v);
    mark[v] = true;
    for (int i : edges[v]) {
        if (!mark[i]) top_sort(i, edges, mark, cur_vertex_in_sort, result);
        else if (found(cur_vertex_in_sort, i)) throw 1;
    }
    result.push_back(v);
}

bool do_sort(int N, vector<vector<int>> &edges, vector<int> &result) {
    vector<int> mark(N + 1, false);
    for (int i = 1; i <= N; i++) {
        unordered_set<int> cur_vertex_in_sort;
        if (!mark[i]) {
            try {
                top_sort(i, edges, mark, cur_vertex_in_sort, result);
            } catch (int a) {
                return false;
            }
        }
    }
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
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges[u].emplace_back(v);
    }

    if (M == 0) {
        for (int i  = 1; i <= N ; i++){
            cout << i << " ";

        }
    } else {
        vector<int> result;
        if (do_sort(N, edges, result)) {
            reverse(result.begin(), result.end());
            for (int i : result)
                cout << i << " ";

        } else {
            cout << "-1";
        }
    }


}

