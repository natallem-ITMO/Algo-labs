#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h>
#include <regex>

using std::vector;
using std::max;
using std::min;
using std::endl;
using std::string;

int getAns(vector<vector<int>> &array, int l, int r, int d) {
    if (l > r) std::swap(l, r);
    l--;
    r;

    printf("l=%d r=%d d=%d\n",l,r,d);
    int min1 = array[l][d];
    int min2 = array[(r - (1 << d))][d];
    return min(min1, min2);
}

int main3() {
    int n, m, a1;
    scanf("%d %d %d", &n, &m, &a1);
    vector<int> arr(n);
    arr[0] = (a1);
    for (int i = 1; i < n; i++) {
         arr[i] = ((arr[i - 1] * 23 + 21563) % 16714589);
        //arr[i] = ((arr[i - 1] * 1 + 2) % 16714589);
    }
    vector<int> d(n);
    int k = 0;
    int twoPk = 2;
    for (int i = 0; i < n; i++) {
        if (i + 1 >= twoPk) {
            k++;
            twoPk <<= 1;
        }
        d[i] = k;
    }
    int logn = ceil(log(n));
    vector<vector<int>> st(n, vector<int>(logn));
    for (int j = 0; j < logn; j++) {
        for (int i = 0; i < n; i++) {
            if ((i + (1 << j)) <= n) {
                if (j == 0) st[i][j] = arr[i];
                else {
                    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }
    printf("vec\n");

    for (int i: arr) {
        printf("%d ", i);
    }
    printf("\n");
    printf("vec d\n");
    for (int i: d) {
        printf("%d ", i);
    }
    printf("\n");
    int u, v;
    scanf("%d%d", &u, &v);
    int ans = getAns(st, u, v, d[v - u]);//here length v-u+1 or v-u
    printf("u=%d v=%d ans=%d \n", u, v,ans);


    for (int i = 0; i < m; i++) {
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * u + 593 + ans + 5 * i) % n) + 1;
        ans = getAns(st, u, v, d[abs(v - u)]);
        printf("u=%d v=%d ans=%d\n", u, v, ans);
        //here i = 0 i = 1

    }

    printf("RESULT %d %d %d", u, v, ans);


    printf("vec\n");

    for (int i: arr) {
        printf("%d ", i);
    }
    printf("\n");
    printf("matr\n");
    for (vector<int> v1 : st) {
        for (int i : v1) {
            printf("%d ", i);

        }
        printf("\n");
    }

    for (int i: d) {
        printf("%d ", i);
    }

    return 0;
}