/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::endl;
using std::string;

void add(vector<vector<vector<int>>> &fen, int x, int y, int z, int value, int n) {
    for (int i = x; i < n; i = (i | (i + 1)))
        for (int j = y; j < n; j = (j | (j + 1)))
            for (int k = z; k < n; k = (k | (k + 1)))
                fen[i][j][k] += value;
}

int sum(vector<vector<vector<int>>> &fen, int x, int y, int z) {
    if (x == -1 || z == -1 || y == -1)
        return 0;
    int result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1)
                result += fen[i][j][k];
    return result;
}

int getAns(vector<vector<vector<int>>> &fen, int x0, int x, int y0, int y, int z0, int z) {
    int value1 = sum(fen, x, y, z) - sum(fen, x0 - 1, y, z) - sum(fen, x, y0 - 1, z) + sum(fen, x0 - 1, y0 - 1, z);
    int value2 = sum(fen, x, y, z0 - 1) - sum(fen, x0 - 1, y, z0 - 1) - sum(fen, x, y0 - 1, z0 - 1) +
                 sum(fen, x0 - 1, y0 - 1, z0 - 1);
    return value1 - value2;
}

int mainLL1() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> pushable(n, vector<int>(n, 0));
    vector<vector<vector<int>>> vec(n, pushable);
    vector<int> result;

    while (true) {
        int command;
        scanf("%d", &command);
        if (command == 1) {
            int x, y, z, value;
            scanf("%d%d%d%d", &x, &y, &z, &value);
            add(vec, x, y, z, value, n);
        }
        if (command == 2) {
            int x0, x, y0, y, z0, z;
            scanf("%d%d%d%d%d%d", &x0, &y0, &z0, &x, &y, &z);
            result.push_back(getAns(vec,x0,x,y0,y,z0,z));

        }
        if (command==3) break;
    }
   // printf("fuck");
    for (int i: result){
        printf("%d\n",i);
    }
   // printf("fuck");


    return 0;
}*/


