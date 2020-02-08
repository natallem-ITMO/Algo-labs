/*#include <iostream>
#include <vector>
#include <stdio.h>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;


int main() {

    long int n, x, y, a0;
    cin >> n >> x >> y >> a0;
    vector<long long int> sum;
    long int aPrev = a0;
    long int aNext;
    for (long int i = 0; i < n; i++) {
        if (i == 0) sum.push_back(a0 % (1 << 16));
        else {
            aNext = ((x * aPrev + y) % (1 << 16));
            sum.push_back(sum[i - 1] + aNext);
            aPrev = aNext;
        }
    }
    long int m, z, t;
    unsigned long int b0;
    cin >> m >> z >> t >> b0;
    unsigned long int bPrev = b0;
    unsigned long long int sumR = 0;
    for (long int i = 0; i < m; i++) {
        unsigned long int b20 = bPrev;
        if (i != 0) b20 = (z * bPrev + t) % (1 << 30);
        unsigned long int b21 = (z * b20 + t) % (1 << 30);
        unsigned long int c1 = b20 % n;
        unsigned long int c2 = b21 % n;
        unsigned long int max1 = max(c1,c2);
        unsigned long int min1 = min(c1,c2);
        if (min1==0) sumR += sum[max1];
        else sumR += (sum[max1]-sum[min1-1]);
        bPrev = b21;
    }
    cout << sumR;



    return 0;
}
*/