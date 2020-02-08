/*
#include <iostream>
//#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

static void showVector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

static void showSet(set<int> &vec) {
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;
}

static void showSet(unordered_set
                            <int> &set) {
    unordered_set<int>::iterator itr;
    for (itr = set.begin(); itr != set.end(); itr++) {
        cout << (*itr) << " ";
    }
    cout << endl;
}

static void showMatrix(vector<vector<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showVector(m[i]);
    }
    cout << endl;
}

static void showMatrixSet(vector<set<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showSet(m[i]);
    }
    cout << endl;
}

static void showMatrixUnorderedSet(vector<unordered_set<int>> &m) {
    for (int i = 0; i < m.size(); i++) {
        showSet(m[i]);
    }
    cout << endl;
}

void showArray(vector<long long int> &vec, int firstIndex){
    for (int i = firstIndex; i < vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}
long long int sum(vector<long long int> &vec, int firstIndex, int l, int r) {
    l--;
    r--;
    l += firstIndex;
    r += firstIndex;
    long long int leftRes = 0;
    long long int rightRes = 0;
    while (l < r) {
        if (l % 2 == 0) leftRes += vec[l];
        l = l / 2;
        if (r % 2 == 1) rightRes += vec[r];
        r = r / 2 - 1;
    }
    if (l == r) leftRes += vec[l];
    return leftRes + rightRes;
}

void add(vector<long long int> &vec, int firstIndex, int ind, long long int value) {
    ind--;
    ind = firstIndex + ind;
    vec[ind] += value;
    ind = (ind - 1) / 2;
    while (ind > 0) {
        vec[ind] = (vec[ind * 2 + 1]) + (vec[ind * 2 + 2]);
        //if (ind == 0) break;
        ind = (ind - 1) / 2;
    }
    if (vec.size() != 1) {
        vec[ind] = (vec[ind * 2 + 1]) + (vec[ind * 2 + 2]);
    }
}

int lca(int a, int b, vector<int> &d, vector<vector<int>> &dp, int log_n) {
    if (d[a] < d[b]) swap(a, b);
    if (d[a] != d[b]) {
        for (int i = log_n; i >= 0; i--) {
            if ((1 << i) <= d[a] - d[b]) {
                a = dp[a][i];
            }
        }
    }
    if (a == b) return a;
    for (int i = log_n; i >= 0; i--) {
        if (dp[a][i] != dp[b][i]) {
            a = dp[a][i];
            b = dp[b][i];
        }
    }
    return dp[a][0];
}

int find_log_2(int x) {//минимальное большее либо равное x
    int i = 0;
    int xi = 1;
    while (true) {
        if (xi >= x) break;
        xi <<= 1;
        i++;
    }
    return i;
}

void dfs(int &time, int vertex, int prev_vertex, vector<list<int>> &connect, vector<int> &depth, vector<vector<int>> &dp,
    vector<int> &begin,
    vector<int> &end, vector<int> &eyler) {
    time++;
    eyler.push_back(vertex);
    begin[vertex] = time;
    int prevDepth = depth[vertex];
    ++prevDepth;
    //  connect[vertex].erase(prev_vertex);
    connect[vertex].remove(prev_vertex);
    for (int son : connect[vertex]) {
        depth[son] = prevDepth;
        dp[son][0] = vertex;
        dfs(time, son, vertex, connect, depth, dp, begin, end, eyler);
        time++;
        eyler.push_back(vertex);
    }
    end[vertex] = time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    int log_n = find_log_2(n);
    vector<vector<int>> dp(n + 1, vector<int>(log_n + 1, 0));
    vector<list<int>> connect(n + 1);
    vector<int> depth(n + 1);
    // vector<int> mark(n + 1);
    vector<int> begin(n + 1);
    vector<int> end(n + 1);
    vector<int> eyler;
    dp[1][0] = 1;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        connect[x].push_back(y);
        connect[y].push_back(x);
    }
    int time = -1;
    dfs(time, 1, -1, connect, depth, dp, begin, end, eyler);

    for (int i = 1; i <= log_n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
        }
    }

//    showMatrix(dp);
//    showVector(depth);
//    showVector(begin);
//    showVector(end);
//    showVector(eyler);
    n = eyler.size();
    int amountOfLeafs = 1;
    int power = 0;
    int amountOfVertices = 0;
    while (n > amountOfLeafs) {
        amountOfVertices += amountOfLeafs;
        amountOfLeafs = (amountOfLeafs << 1);
        power++;
    }
    amountOfVertices += amountOfLeafs;
    int firstIndex = (1 << (power)) - 1;
    // printf("vertices=%d, leafs=%d, power=%d, firstInd=%d", amountOfVertices, amountOfLeafs, power, firstIndex);

    vector<long long int> array(amountOfVertices, 0);
    char command;
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> command;
        switch (command){
            case '+':{
                int x, y;
                long long int d;
                cin >> x >> y >> d;
                add(array,firstIndex, begin[x] +1, d);
                //showArray(array, firstIndex);
                add(array, firstIndex, begin[y] + 1, d);
                int lca_node = lca(x, y,depth, dp, log_n);
                add(array,  firstIndex, begin[ lca_node]+1, -d);
                int lca_parent = dp[lca_node][0];
                if (lca_node!= lca_parent)
                add(array, firstIndex, begin[dp[lca_node][0]]+1, -d);
               // showArray(array, firstIndex);
                break;
            }
            case '?':{
                int x;
                cin >> x;
                cout << sum(array, firstIndex, begin[x]+1, end[x]+1 )<<endl;
                break;
            }
        }
    }

*/
/*
    int curIndex = firstIndex - 1;
    while (cin >> command) {
        long long int a, b;
        cin >> a >> b;
        if (command == "sum") {
            result.push_back(sum(array, firstIndex, a, b));
        } else if (command == "set") {
            set(array, firstIndex, a, b);
        }
    }
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
    *//*

    return 0;
}

*/
