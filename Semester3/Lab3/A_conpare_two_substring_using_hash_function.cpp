#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const uint32_t M = 12398247;

const uint32_t x = 47;

vector<uint32_t > pow;

vector<uint32_t > hashes;

void create_pow(int n){
   pow.resize(n+1);
   pow[0] = 1;
   for (int i = 1; i <=n; i++) {
       uint64_t p = (uint64_t) x * pow[i-1];
       p %= M;
       pow[i] = p;
   }
}

void create_P_hashes(const string & s){
    vector<uint32_t >& hashes1 = hashes;

    int n = s.length();
    vector<uint32_t > &pow1 = pow;

    hashes.resize(n+1);
    hashes[0] = 0;

    for (int i = 1; i <= n; i++){
        hashes[i] = (hashes[i-1]* x + (s[i-1]-'a'+1)) % M;
    }

}

uint32_t get_hash(size_t l, size_t r ){//r not include
    uint32_t a = hashes[r];
    if (a==0) a= M;
    uint64_t b= hashes[l];
    if (b==0) b= M;
    uint64_t X = pow[r-l];
    uint64_t bb = (b*X) % M;
    if (a < bb) {
        a += M;
    }
    return (a - bb) % M;
}

int main(){
#ifdef MY_DEBUG
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    vector<uint32_t > &pow1 = pow;

    vector<uint32_t >& hashes1 = hashes;

    string s;
    int n;
    cin >> s >> n;

    create_pow(s.length());
    create_P_hashes(s);

    for (int i = 0; i < n; i++){
        int a, b,c, d;
        cin >> a >> b >> c >> d;
        if (get_hash(a-1,b) == get_hash(c-1, d)){
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }


}