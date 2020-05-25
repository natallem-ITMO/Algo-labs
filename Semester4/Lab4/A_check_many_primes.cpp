#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;
using ull = unsigned long long;
int MAX = 20000000;

vector<bool> getSieve(){
    vector<bool> sieve(MAX+1, false);
    for (int i = 2; i < MAX; i++){
        if (sieve[i]==0){
            for (int j = 2; ; j++){
                int s = j * i;
                if (s >= MAX) break;
                sieve[s]=true;
            }
        }
    }
    return  sieve;
}

int main() {
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    auto sieve = getSieve();
    int n ;
     cin >> n;
     for (int i = 0; i < n;i++){
         int a;
         cin >> a;
         if (sieve[a]) cout << "NO\n";
         else cout << "YES\n";
     }


    return 0;
}
