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

const long long int MAX = 1000000000000000008;
vector<long long int> array;
vector<long long int> dAdd;
vector<long long int> dSet;
int firstIndex;



void push2(int node) {
    if (node >= firstIndex) return;
    int ls = 2 * node + 1;
    int rs = 2 * node + 2;
    if (dSet[node] != MAX) {
        dAdd[ls] = 0;
        dAdd[rs] = 0;
        dSet[ls] = dSet[node];
        dSet[rs] = dSet[node];
    } else {
        if (dSet[ls] != MAX) {
            dSet[ls] += dAdd[node];
        } else {
            dAdd[ls] += dAdd[node];
        }
        if (dSet[rs] != MAX) {
            dSet[rs] += dAdd[node];
        } else {
            dAdd[rs] += dAdd[node];
        }
    }
    dSet[node] = MAX;
    dAdd[node] = 0;
}

long long int trueValue(int node) {
    long long int res;
    if (dSet[node] == MAX) {
        res = array[node] + dAdd[node];
        return res;
    } else {
        res = dSet[node];
        return res;
    }
}

void updateSet(int node, long long int value) {
    dSet[node] = value;
    dAdd[node] = 0;
}

void updateAdd(int node, long long int value) {
    if (dSet[node] != MAX) {
        dSet[node] += value;
        dAdd[node] = 0;
    } else {
        dAdd[node] += value;
    }
}

void addTo(int l, int r, int node, long long int value, int L,
           int R) {//L R исходные границы, l r запрос, правая граница не включена
    if (L >= r || R <= l) return;
    if (L >= l && R <= r) {
        updateAdd(node, value);
        return;
    }
    push(node);
    addTo(l, r, 2 * node + 1, value, L, (L + R) / 2);
    addTo(l, r, 2 * node + 2, value, (L + R) / 2, R);
    array[node] = min(trueValue(2 * node + 1), trueValue(2 * node + 2));
}

void setTo(int l, int r, int node, long long int value, int L,
           int R) {//L R исходные границы, l r запрос, правая граница не включена
    if (L >= r || R <= l) return;
    if (L >= l && R <= r) {
        updateSet(node, value);
        return;
    }
    push(node);
    setTo(l, r, 2 * node + 1, value, L, (L + R) / 2);
    setTo(l, r, 2 * node + 2, value, (L + R) / 2, R);
    array[node] = min(trueValue(2 * node + 1), trueValue(2 * node + 2));
}

long long int getMin(int l, int r, int node, int L, int R) {//L R исходные границы, l r запрос, правая граница не включена
    if (L >= r || R <= l) return MAX;
    if (L >= l && R <= r) return trueValue(node);
    push(node);
    long long int ans = min(getMin(l, r, 2 * node + 1, L, (L + R) / 2), getMin(l, r, 2 * node + 2, (L + R) / 2, R));
    array[node] = min(trueValue(2 * node + 1), trueValue(2 * node + 2));
    return ans;
}

int main3() {
    int n;
    cin >> n;

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
    //   printf("vertices=%d, leafs=%d, power=%d, firstInd=%d", amountOfVertices, amountOfLeafs, power, firstIndex);

    int start = firstIndex;
    int end = firstIndex + n - 1;
    for (int i = 0; i < amountOfVertices; i++) {
        array.push_back(MAX);
        dAdd.push_back(0);
        dSet.push_back(MAX);
        if (i >= start && i <= end) {
            cin >> array[i];
        }
    }
    int curIndex = firstIndex - 1;
    while (curIndex >= 0) {
        array[curIndex] = min(array[curIndex * 2 + 1], array[curIndex * 2 + 2]);
        curIndex--;
    }
    //showVector(&array);
    vector<long long int> result;
    string command;
    while (cin >> command) {
        if (command == "min") {
            int l, r;
            cin >> l >> r;
            result.push_back(getMin(l - 1, r, 0, 0, amountOfLeafs));
        } else if (command == "set") {
            int l, r;
            long long int value;
            cin >> l >> r >> value;
            setTo(l - 1, r, 0, value, 0, amountOfLeafs);
        } else if (command == "add") {
            int l, r;
            long long int value;
            cin >> l >> r >> value;
            addTo(l - 1, r, 0, value, 0, amountOfLeafs);
        } else {
            break;
        }
    }
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }

    return 0;
}
*/