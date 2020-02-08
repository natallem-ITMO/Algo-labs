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
    vector<int> z(n + 1, 0);
   int l,r;
   l=0;
   r= 1;
   for (int i = 1; i < n; i++){
       int b= r-i;
       if (b < 0 ) b = 0;
       z[i] = min(z[i - l], b);
       int & zi = z[i];

       while (s[i+z[i]]==s[z[i]]){
           char ch1 = s[z[i]];
           char ch2 = s[i+z[i]];
           z[i]++;
       }
       if (i+z[i] > r){
           l=i;
           r=i+z[i];
       }
   }

    for (int i = 1; i <n;  i++){
        cout << z[i] << " ";
    }


}