/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <map>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;

const int noIncline = -1;

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
    vec[node] = max(trueValue(vec, dAdd,getLs(node)), trueValue(vec, dAdd, getRs(node)));

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
    int trueValLs = trueValue(vec,dAdd,ls);
    int rs = getRs(node);
    int trueValRs = trueValue(vec,dAdd,rs);

    // int vecnode = vec[node];
    if (trueValLs == trueValue(vec,dAdd,node)) return getMaxIndex(vec, dAdd, ls);
    else return getMaxIndex(vec, dAdd, rs);

}

int getMax(vector<int> &vec, vector<int> &dAdd) {
    return trueValue(vec, dAdd, 0);
}

int main() {
    map<int,vector<vector<int>>> map;
    int MAX = 2000002;
    int plus = 0;
    int maxX = -MAX;
    int minY = MAX;
    int maxY = -MAX;
    int req;
    scanf("%d",&req);
    std::map<int,vector<vector<int>>>::iterator it;
    for (int i = 0; i < req; i++){
        int x1,x2,y1,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        maxX = max(x2,maxX);
        minY = min(y1,minY);
        maxY = max(y2, maxY);
        int key1 = x1;
        int key2 = x2+1;
        vector<int> value1 = {1,y1,y2};
        vector<int> value2 = {0,y1,y2};
        it = map.find(key1);
        if (it==map.end()){
            map.insert({key1,  {value1}});
        } else {
            it->second.push_back(value1);
        }
        it = map.find(key2);
        if (it==map.end()){
            map.insert({key2, {value2}});
        } else {
            it->second.push_back(value2);
        }
    }
    if (minY<0) plus = -minY;
    int n = maxY-minY+1;
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


    vector<int> vec(amountOfVertices, 0);
    vector<int> dAdd(amountOfVertices, 0);
    int maxOnTable = -1;
    int indexY;
    int indexX;

    for(it = map.begin(); it != map.end(); ++it) {
        int x = it -> first;
        if (x <= maxX) {
            vector<vector<int>> blocks = it->second;
            for (vector<int> partWin: blocks) {
                int addNum = (partWin[0] == 1) ? 1 : -1;
                int l = partWin[1] + plus;
                int r = partWin[2] + plus;
                addTo(vec, dAdd, l, r + 1, 0, addNum, 0, amountOfLeafs);
            }
            // pushAll(vec,dAdd,0,amountOfVertices);
            int curMax = getMax(vec, dAdd);
            int gettedMaxined = getMaxIndex(vec, dAdd, 0);
            int curIndexYMax = gettedMaxined - firstIndex;
            if (curMax > maxOnTable) {
                maxOnTable = curMax;
                indexY = curIndexYMax - plus;
                indexX = x;
            }
        }
    }
    printf("%d\n%d %d",maxOnTable,indexX, indexY);

   // cout << getMax(vec,dAdd)<<" "<<getMaxIndex(vec,dAdd,0);

    return 0;
}
*/