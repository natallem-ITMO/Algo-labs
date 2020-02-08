/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <map>
#include <algorithm>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;


int firstIndex;

int getRs(int node) {
    return node * 2 + 2;
}

int getLs(int node) {
    return getRs(node) - 1;
}

int trueValue(vector<int> &vec, vector<int> &dAdd, int node) {
    return vec[node] + dAdd[node];
}

void push(vector<int> &vec, vector<int> &dAdd, int node) {
    if (node >= firstIndex) {
        vec[node] = vec[node] + dAdd[node];
        dAdd[node] = 0;
        return;
    }
    int ls = 2 * node + 1;
    int rs = 2 * node + 2;
    dAdd[ls] += dAdd[node];
    dAdd[rs] += dAdd[node];
    dAdd[node] = 0;
    vec[node] = max(trueValue(vec, dAdd, getLs(node)), trueValue(vec, dAdd, getRs(node)));

}

void pushAll(vector<int> &vec, vector<int> &dAdd, int node, int amountOfVeticals) {
    for (int i = 0; i < amountOfVeticals; i++) {
        push(vec, dAdd, i);

    }
}

void addTo(vector<int> &vec, vector<int> &dAdd, int l, int r, int node, int value, int L,
           int R) {//L R исходные границы, l r запрос, правая граница не включена
    if (L >= r || R <= l) return;
    if (L >= l && R <= r) {
        dAdd[node] += value;
        return;
    }
    push(vec, dAdd, node);
    addTo(vec, dAdd, l, r, 2 * node + 1, value, L, (L + R) / 2);
    addTo(vec, dAdd, l, r, 2 * node + 2, value, (L + R) / 2, R);
    vec[node] = max(trueValue(vec, dAdd, 2 * node + 1), trueValue(vec, dAdd, 2 * node + 2));
}

int getMaxIndex(vector<int> &vec, vector<int> &dAdd, int node) {
    push(vec, dAdd, node);
    if (node >= firstIndex) return node;
    int ls = getLs(node);
    int trueValLs = trueValue(vec, dAdd, ls);
    int rs = getRs(node);
    int trueValRs = trueValue(vec, dAdd, rs);
    if (trueValLs == trueValue(vec, dAdd, node)) return getMaxIndex(vec, dAdd, ls);
    else return getMaxIndex(vec, dAdd, rs);

}

int getMax(vector<int> &vec, vector<int> &dAdd) {
    return trueValue(vec, dAdd, 0);
}

int main() {

    vector<vector<int>> vv;
    int MAX = 2000002;
    int plus = 0;
    int maxX = -MAX;
    int minY = MAX;
    int maxY = -MAX;
    int req;
    scanf("%d", &req);

    for (int i = 0; i < req; i++) {
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        maxX = max(x2, maxX);
        minY = min(y1, minY);
        maxY = max(y2, maxY);
        vector<int> value1 = {x1, 1, y1, y2};
        vector<int> value2 = {x2 + 1, 0, y1, y2};
        vv.push_back(value1);
        vv.push_back(value2);

    }

    std::sort(vv.begin(), vv.end(),
              [](const std::vector<int> &a, const std::vector<int> &b) {
                  return  a[0] < b[0] || a[0] == b[0] && a[1] > b[1];
              });
    if (minY < 0) plus = -minY;
    int n = maxY - minY + 1;
    int amountOfLeafs = 1;
    int power = 0;
    int amountOfVertices = 0;
    while (n > amountOfLeafs) {
        amountOfVertices += amountOfLeafs;
        amountOfLeafs = (amountOfLeafs << 1);
        power++;
    }
    amountOfVertices += amountOfLeafs;
    firstIndex = (1 << (power)) - 1;
    vector<int> vec(amountOfVertices, 0);
    vector<int> dAdd(amountOfVertices, 0);
    int maxOnTable = -1;
    int indexY;
    int indexX;

    vector<vector<vector<int>>> vvv;
    vvv.push_back({vv[0]});
    for (int j = 1; j < vv.size(); j++) {
        vector<int> vector1 = vv[j];
        if (vector1[0] == vvv[vvv.size() - 1][0][0]) vvv[vvv.size() - 1].push_back(vector1);
        else vvv.push_back({vector1});
    }
    for (int i = 0; i < vvv.size(); i++) {

        int x = vvv[i][0][0];
        if (x <= maxX) {
           vector<vector<int>> block = vvv[i];

            for (vector<int> partWin: block) {
                int addNum = (partWin[1] == 1) ? 1 : -1;
                int l = partWin[2] + plus;
                int r = partWin[3] + plus;
                addTo(vec, dAdd, l, r + 1, 0, addNum, 0, amountOfLeafs);
            }
            int curMax = getMax(vec, dAdd);
            int gettedMaxIndex = getMaxIndex(vec, dAdd, 0);
            int curIndexYMax = gettedMaxIndex - firstIndex;
            if (curMax > maxOnTable) {
                maxOnTable = curMax;
                indexY = curIndexYMax - plus;
                indexX = x;
            }
        }
    }
    printf("%d\n%d %d", maxOnTable, indexX, indexY);
    return 0;
}*/
