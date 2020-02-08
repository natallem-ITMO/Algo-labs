//
// Created by natalem on 27.10.2019.
//

//
// Created by natalem on 17.10.2019.
//


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
int main() {

#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    cin >> N;
    vector<vector<int>> d(N+1, vector<int>(N+1));
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cin >> d[i][j];
        }
    }
    for (int k = 1; k <= N; k++){
        for (int i = 1; i <= N; i++){
            for (int j = 1; j <= N; j++){

                d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
            }
        }
//        show_collection(d, "k="+to_string(k)+"\n");
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cout << d[i][j] << " ";
        }
        cout << "\n";
    }
   // show_collection(d);

}