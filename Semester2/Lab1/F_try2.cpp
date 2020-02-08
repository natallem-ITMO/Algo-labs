#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h>
#include <regex>

using std::vector;
using std::max;
using std::min;

//ищет мин элемент в массиве от л до р включительно
int getMin(vector<vector<int>> &st, vector<int> &a, int l, int r, int d) {
   // if (d==-1) return a[l];
    return min(st[l][d], st[r - (1 << d) + 1][d]);
}

int fl(int len){
    if (len == 1)    return 0;
    else return fl(floor(len/2)) +1;
}

int main56() {
    int n, m, a;
    scanf("%d%d%d", &n, &m, &a);
    vector<int> aa(n);
    aa[0] = a;
    int MAX = 16714589 + 100;
    for (int i = 1; i < n; i++) {
        a = (23 * a + 21563) % 16714589;
        //a = (2 * a + 4) % 19;
        aa[i] = a;
    }

    vector<int> d(n + 1);
   /* d[0] = -1;
    d[1] = 0;
    //  d[2] = 1;

    int curPower = 0;
    int nextTwo = 2;
    for (int i = 2; i <= n + 1; i++) {
        if (nextTwo <= i) {
            d[i] = ++curPower;
            nextTwo <<= 1;
        } else {
            d[i] = curPower;
        }
    }*/
   for (int i = 1; i <= n ; i++){
       d[i] = fl(i);
   }

   // int logn = ceil(log10(n)/log10(2));
    int logn = fl(n) +1;
   // printf("%d logn\n", logn);
    vector<vector<int>> st(n, vector<int>(logn+1));
    for (int j = 0; j <= logn; j++) {
       // int twoPowerJ = (j == 0) ? 0 : (1 << j);
        for (int i = 0; i < n; i++) {
            if (i + (1 << j) <= n) {
                if (j == 0) st[i][j] = aa[i];
                else st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }/*
    printf("%d logn\n", logn);
    for (int i : d) {
        printf("%d ", i);
    }
    printf("\narray\n");

    for (int i : aa) {
        printf("%d ", i);
    }
    printf("\nmatrix\n");

    for (vector<int> v1 : st) {
        for (int i : v1) {
            printf("%d ", i);
        }
        printf("\n");
    }*/


    int l, r, dd;
    int u, v;
    scanf("%d%d", &u, &v);
    l = u - 1;
    r = v - 1;
    dd = d[r - l + 1];
    int ans = getMin(st,aa, l, r, dd);
    for (int i = 1; i < m; i++) {
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
        l = min(u, v) - 1;
        r = max(u, v) - 1;
        dd = d[r - l + 1];
        ans = getMin(st,aa, l, r, dd);
    }
    printf("%d %d %d", u, v, ans);
    //printf("fds");
}
