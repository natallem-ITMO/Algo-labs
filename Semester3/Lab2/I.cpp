
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct point {

    point() {
        condition = 0;
        output_edges_amount = 0;
        to_win = to_fail = 0;
        in_queue = false;
    }

    vector<int> input_edges;
    int condition;
    int output_edges_amount;
    int to_win;
    int to_fail;
    bool in_queue;
};

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    while (cin >> n) {
        int m;
        cin >> m;
        vector<point> vec(n + 1);

        unordered_map<int, vector<int>> reverseEdges;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            vec[b].input_edges.push_back(a);
            vec[a].output_edges_amount++;
        }
        queue<int> queue;
        for (int i = 1; i <= n; i++) {
            if (vec[i].output_edges_amount == 0) {
                vec[i].in_queue = true;
                queue.push(i);
            }
        }
        while (!queue.empty()) {
            int i = queue.front();
            queue.pop();
            point &u = vec[i];
            if (u.to_win == u.output_edges_amount) {
                u.condition = -1;
                for (int j : u.input_edges) {
                    point &v = vec[j];
                    v.to_fail++;
                    if (!v.in_queue) {
                        v.in_queue = true;
                        queue.push(j);
                    }
                }
            } else if (u.to_fail > 0) {
                u.condition = 1;
                for (int j : u.input_edges) {
                    point &v = vec[j];
                    v.to_win++;
                    if (!v.in_queue && v.to_win == v.output_edges_amount) {
                        v.in_queue = true;
                        queue.push(j);
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            string s;
            switch (vec[i].condition) {
                case 1:
                    s = "FIRST";
                    break;
                case 0:
                    s = "DRAW";
                    break;
                case -1:
                    s = "SECOND";
                    break;
            }
            cout << s << "\n";
        }
        cout << "\n";
    }
}

