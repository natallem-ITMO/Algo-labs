
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int r1, p1, s1, r2, p2, s2;
    cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
    vector<int> v = {s1 - s2 - r2, r1 - r2 - p2, p1 - p2 - s2};
    int maxx = 0;
    for (int a : v){
        maxx = max(maxx, a);
    }
    cout << maxx;
    return 0;
}
