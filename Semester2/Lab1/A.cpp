/*#include <iostream>
#include <vector>
#include <stdio.h>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;


 void showVector(vector<unsigned int> *vector1) {
    for (long long int i : *vector1) {
        cout << i << " ";
    }
    cout << endl;
}

void showVector(vector<long long unsigned int> *vector1) {
    for (long long unsigned int i : *vector1) {
        cout << i << " ";
    }
    cout << endl;
}

void showVector(vector<long long int> *vector1) {
    for (long long int i : *vector1) {
        cout << i << " ";
    }
    cout << endl;
}



int main() {

    vector<long long int> suma;
    //vector<unsigned int> c;

    long long int n, x, y, a0, m, z, b0;
    long long int t;
    cin >> n >> x >> y >> a0 >> m >> z >> t >> b0;

    long long int aprev = a0;

    for (int i = 0; i < n; i++) {
        if (i == 0) suma.push_back(aprev);
        else suma.push_back(suma[i - 1] + (x * aprev + y));
        if (i == 0) aprev = a0;
        else aprev = x * aprev + y;
    }
    unsigned long long int bprev = b0;
    unsigned long long int cCur = b0 % n;
    unsigned long long int cPrev;
    long long int sum = 0;
    for (long int i = 0; i <= m * 2; i++) {

        if (i == 0) cCur = b0 % n;
        else {
            cPrev = cCur;
            cCur = ((z * bprev + t) % (1 << 30)) % n;
        }
        if (i == 0) bprev = b0;
        else bprev = ((z * bprev + t) % (1 << 30));
        if (i % 2 != 0) {
            if (min(cCur, cPrev) == 0) sum += (suma[max(cCur, cPrev)]);
            else sum += (suma[max(cCur, cPrev)] - suma[min(cCur, cPrev) - 1]);
        }
    }
}
*/
