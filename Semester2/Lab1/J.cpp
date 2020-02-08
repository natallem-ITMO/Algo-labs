/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
int firstIndex;
int lastIndex;
int MAX = 1000000000;

int getRs(int node) {
    return node * 2 + 2;
}

int getLs(int node) {
    return getRs(node) - 1;
}

void push(vector<int> &vec, int node) {
    if (node >= firstIndex)
        return;
    int ls = getLs(node);
    int rs = getRs(node);
    vec[ls] = max(vec[ls], vec[node]);
    vec[rs] = max(vec[rs], vec[node]);
}

void setMin(vector<int> &vec, int valueMin, int node, int l, int r, int L, int R) {
    if (L >= r || R <= l) return;
    if (L >= l && R <= r) {
        if (vec[node] < valueMin) vec[node] = valueMin;
        return;
    }
    push(vec, node);
    int ls = getLs(node);
    int rs = getRs(node);
    int m = (L + R) / 2;
    setMin(vec, valueMin, ls, l, r, L, m);
    setMin(vec, valueMin, rs, l, r, m, R);
    vec[node] = min(vec[ls], vec[rs]);
}


vector<int> findMin(vector<int> &vec, int node, int l, int r, int L, int R) {
    push(vec,node);
    if (L >= r || R <= l) {
        int k = 0;
        return {MAX, -1};
    }

    if (L >= l && R <= r) {
        return {vec[node], node};
    }

    int ls = getLs(node);
    int rs = getRs(node);
    int m = (L + R) / 2;
    vector<int> lsRes = findMin(vec, ls, l, r, L, m);
    vector<int> rsRes = findMin(vec, rs, l, r, m, R);
    if (lsRes[0] < rsRes[0]) return lsRes;
    else return rsRes;
}

int findMinIndex(vector<int> &vec, int node) {
    push(vec, node);
    if (node >= firstIndex) return node;
    if (vec[getLs(node)] == vec[node]) findMinIndex(vec, getLs(node));
    else findMinIndex(vec, getRs(node));
}

int main() {
    int n;
    int m;
    scanf("%d", &n);

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
    lastIndex = firstIndex + n - 1;
    vector<int> vec(amountOfVertices, MAX);
    for (int i = firstIndex; i <= lastIndex; i++) {
        vec[i] = 0;
    }

    for (int i = firstIndex - 1; i >= 0; i--) {
        vec[i] = min(vec[2 * i + 1], vec[2 * i + 2]);
    }
    scanf("%d", &m);
    string command;
    vector<string> result;

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> command >> l >> r;
        if (command == "defend") {
            int high;
            cin >> high;
            setMin(vec, high, 0, l - 1, r, 0, amountOfLeafs);

        } else if (command == "attack") {
            vector<int> res = findMin(vec, 0, l - 1, r, 0, amountOfLeafs);
            int index = findMinIndex(vec, res[1]);
            result.push_back(std::to_string(res[0]) + " " + std::to_string(index-firstIndex+1));
        } else break;
    }


    for (string i : result) {
        cout << i << std::endl;
    }
    return 0;
}*/


