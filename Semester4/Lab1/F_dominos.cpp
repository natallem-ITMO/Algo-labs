#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
//#include "../../../Helper/show_collections.hpp"

bool debug = false;

using namespace std;

vector<vector<int>> matrix;
int n, m;

void showMatching(vector<int> &t, int i) {
    printf("matching %d : \n", i);
    for (int i = 0; i < t.size(); i++) {
        printf("%d -> %d\n", i, t.at(i));
    }
}

bool dfs(int i, vector<vector<int>> &edges, vector<int> &matching, vector<bool> &visited) {

    if (visited[i]) return false;
    visited[i] = true;
    for (int j : edges[i]) {
        if (matching[j] == -1 || dfs(matching[j], edges, matching, visited)) {
            matching.at(j) = i;
            return true;
        }
    }
    return false;
}

vector<int> find_matching(vector<vector<int>> &edges, int n, int m) {   // A | B
    //return max matching to B
    //m is for B. n is for A
    vector<int> matching(m, -1);
    vector<bool> visited(n);
    for (int i = 0; i < n; i++) {
        fill(visited.begin(), visited.end(), false);
        dfs(i, edges, matching, visited);
        if (debug) showMatching(matching, i);
    }
    return matching;

}


int &left(int i, int j) {
    return matrix.at(i).at(j - 1);
}

int &right(int i, int j) {
    return matrix.at(i).at(j + 1);
}

int &up(int i, int j) {
    return matrix.at(i - 1).at(j);
}


int &down(int i, int j) {
    return matrix.at(i + 1).at(j);
}

void bfs(int i, int j, int color) {
    if (matrix[i][j] != 5) return;
    matrix[i][j] = color;

    if (i > 0) {
        bfs(i - 1, j, color ^ 3);
    }
    if (i < n - 1) {
        bfs(i + 1, j, color ^ 3);
    }
    if (j > 0) {
        bfs(i, j - 1, color ^ 3);
    }
    if (j < m - 1) {
        bfs(i, j + 1, color ^ 3);
    }
}


int main() {

#ifdef MY_DEBUG
    debug = true;
//    std::ifstream cin("a.in");
//    std::ofstream cout("a.out");
#endif
    std::ifstream cin("dominoes.in");
    std::ofstream cout("dominoes.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int a, b;
    cin >> n >> m >> a >> b;
    matrix.resize(n, vector<int>(m, 0));
    int counter = 0;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            if (s.at(j) == '*') {
                counter++;
                matrix.at(i).at(j) = 5;
            }
        }
    }
    if ((a >= 2 * b && a > 0) || (a < 0 && 2 * b <= a)) {
        cout << counter * b;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 5) {
                bfs(i, j, 1);
            }
        }
    }
    int A = 0;
    int B = 0;
    vector<vector<int>> names(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix.at(i).at(j) == 1) {
                names.at(i).at(j) = A++;
            }
            if (matrix.at(i).at(j) == 2) {
                names.at(i).at(j) = B++;
            }
        }
    }
    vector<vector<int>> edges(A, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix.at(i).at(j) == 1) {
                int name = names.at(i).at(j);
                if (i > 0 && up(i, j)) {
                    edges.at(name).push_back(names.at(i - 1).at(j));
                }
                if (i < n - 1 && down(i, j)) {
                    edges.at(name).push_back(names.at(i + 1).at(j));
                }
                if (j > 0 && left(i, j)) {
                    edges.at(name).push_back(names.at(i).at(j - 1));
                }
                if (j < m - 1 && right(i, j)) {
                    edges.at(name).push_back(names.at(i).at(j + 1));
                }
            }
        }
    }
    int doubles;
    auto t = find_matching(edges, A, B);
    doubles = 0;
    for (int d : t) {
        if (d != -1) doubles++;
    }
    cout << (counter - doubles * 2) * b + doubles * a;
    return 0;
}