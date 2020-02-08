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
#include <algorithm>

using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");
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

static void showVector(vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
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

using namespace std;

int main() {
    int n;
    cin >> n;
    if (n==1) {
        cout << "1: ";
    } else {
        //vector<int> p(n);
//    for (int i = 0; i < n; i++) {
//        cin >> p[i];
//    }
        int x = find_log_2(n);
        vector<int> sample(x, 0);
        vector<vector<int>> dp(n, vector<int>(x, 0));
        // showMatrix(dp);
        for (int i = 0; i < n; i++) {
            cin >> dp[i][0];
        }
        //   showMatrix(dp);
        for (int i = 1; i < x; i++) {
            for (int j = 0; j < n; j++) {
                //  printf("i(i)=%d j(vertix)=%d predok=%d\n",i, j,dp[j][i-1] );
                int ans = dp[j][i - 1];
                if (ans == 0) ans = j; else --ans;
                dp[j][i] = dp[ans][i - 1];
            }
            //  showMatrix(dp);
        }
        // showMatrix(dp);
        for (int i = 0; i < n; i++) {
            cout << (i + 1) << ": ";
            for (int j = 0; j < x; j++) {
                if (dp[i][j] != 0) cout << dp[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}