#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


int main(){
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin >> s;
    int n = s.length();
    vector<int> p(n+1,0);
    p[0]=-1;
    for (int i = 1; i <= n; i++){
        int k = p[i-1];
        while (k>=0){
            if (s[k]==s[i-1]){
                p[i] = k+1;
                break;
            } else {
                k=p[k];
            }
        }
    }
    int k = (n-p[n]);
    if ((n % k) ==0){
        cout << k;

    } else {
        cout << n;
    }
//    for (int i = 1; i <=n;  i++){
//        cout << p[i] << " ";
//    }


}