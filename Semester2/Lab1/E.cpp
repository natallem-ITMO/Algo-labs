/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using std::vector;
using std::max;
using std::min;
using std::endl;
using std::string;

vector<vector<int>> matrix;
int firstIndex;
int r;

vector<int> mulMat(vector<int> mat1, vector<int> mat2) {
    vector<int> res(4);
    res[0] = ((mat1[0] * mat2[0]) + (mat1[1] * mat2[2])) % r;
    res[1] = ((mat1[0] * mat2[1]) + (mat1[1] * mat2[3])) % r;
    res[2] = ((mat1[2] * mat2[0]) + (mat1[3] * mat2[2])) % r;
    res[3] = ((mat1[2] * mat2[1]) + (mat1[3] * mat2[3])) % r;
    return res;
}

vector<int> find(int l, int r, int node, int L, int R) {//L R исходные границы, l r запрос, правая граница не включена
    if (L >= r || R <= l) {
        return {1, 0, 0, 1};
    }
    if (L >= l && R <= r) {
        return matrix[node];
    }
    int M = (L + R) / 2;
    return mulMat(find(l, r, 2 * node + 1, L, M), find(l, r, 2 * node + 2, M, R));
}


int main() {

    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    int n, m;
    scanf("%d%d%d", &r, &n, &m);

    int amountOfLeafs = 1;
    int power = 0;
    int amountOfVertices = 0;
    while (n > amountOfLeafs) {
        amountOfVertices += amountOfLeafs;
        amountOfLeafs = (amountOfLeafs << 1);
        power++;
    }
    //printf("her");
    amountOfVertices += amountOfLeafs;
    firstIndex = (1 << (power)) - 1;
    vector<int> emptyV = {1, 0, 0, 1};
    vector<int> input(4);

    int start = firstIndex;
    int end = firstIndex + n - 1;
    for (int i = 0; i < amountOfVertices; i++) {
        if (i >= start && i <= end) {
            scanf("%d%d%d%d", &input[0], &input[1], &input[2], &input[3]);
            for (int j = 0 ;j < 4; j++){
                input[j] %= r;
            }


            matrix.push_back(input);
        } else matrix.push_back(emptyV);
    }
    int curIndex = firstIndex - 1;
    while (curIndex >= 0) {
        matrix[curIndex] = mulMat(matrix[curIndex * 2 + 1], matrix[curIndex * 2 + 2]);
        curIndex--;
    }
    vector<int> a;
    // printf("Fuck");
    for (int i = 0; i < m; i++) {
        int L, R;
        scanf("%d%d", &L, &R);
        a = find(L - 1, R, 0, 0, amountOfLeafs);
        // printf("%d - \n",i);
        printf("%d %d\n%d %d\n\n", a[0], a[1], a[2], a[3]);
    }
    return 0;
}*/