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

vector<int> segments;
vector<int> r1;
vector<int> l1;
vector<int> sum;
vector<short> d;
int firstIndex;
void showVector(vector<unsigned int> *vector1) {
    for (long long int i : *vector1) {
        cout << i << " ";
    }
    cout << endl;
}
void showVector(vector<short> *vector1, string s) {
    cout << s<<": ";

    for (short i : *vector1) {
        cout << i << " ";
    }
    cout << endl;
}
void showVector(vector<int> *vector1, string s) {
    cout << s<<": ";
    for (int i : *vector1) {
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



int getRs(int node) {
    return node * 2 + 2;
}

int getLs(int node) {
    return getRs(node) - 1;
}

void push(int node) {
    if (node >= firstIndex)
        return;;
    int ls = getLs(node);
    int rs = getRs(node);
    if (d[node] != -1) {
        d[ls] = d[node];
        d[rs] = d[node];
        d[node] = -1;
    }
    //showAll("afterPush "+ std::to_string(node));
}

vector<int> trueValue(int node, int length) {
    vector<int> res;
    if (d[node] == 1) {
        res = {1, 1, 1, length};
    } else if (d[node] == 0) {
        res = {0,0,0,0};
    } else {
        res = {segments[node], l1[node], r1[node], sum[node]};
    }
    return res;
}

void setValue(int node, int l, int r, int ls, int rs) {
    int length = (r-l )/2;
    vector<int> lvec = trueValue(ls,(r-l)/2);
    vector<int> rvec = trueValue(rs,(r-l)/2);
    segments[node] = lvec[0]+rvec[0];
    if (lvec[1] && rvec[2]) segments[node]--;
    r1[node] = lvec[2];
    l1[node] = rvec[1];
    sum[node] = lvec[3] + rvec[3];
    vector<int> resvec = {segments[node], l1[node], r1[node], sum[node]};
    //showAll("afterSetvalue "+std::to_string(node));

}

void update(int l, int r, int node, int value, int L, int R) {//L R исходные границы, l r запрос, правая граница не включена
    if (L >= r || R <= l) return;
    if (L >= l && R <= r) {
        d[node] = value;
        return;
    }
    push(node);
    int ls = getLs(node);
    int rs = getRs(node);
    update(l, r, ls, value, L, (L + R) / 2);
    update(l, r, rs, value, (L + R) / 2, R);
    setValue(node,L,R,ls,rs);
    //array[node] = min(trueValue(2 * node + 1), trueValue(2 * node + 2));
}



int main() {

    int n;
    cin >> n;
    vector<short> color(n, 0);
    vector<int> start(n);
    vector<int> end(n);
    int maxb = 0;
    for (int i =0; i < n;i++){
        char ch;
        cin >> ch;
        int a,b;
        cin >> a >> b;
        b+= a;
        a+=500000;
        b+=500000;
        start[i] = a;
        end[i] = b;
        maxb = max(maxb, b);
        if (ch=='B') color[i] =1;
    }
    //showVector(&start,"start");
  //  showVector(&end,"end");
    //showVector(&color,"end");



    int n1 = maxb;
    //printf("n1 = %d", n1);

    int amountOfLeafs = 1;
    int power = 0;
    int amountOfVertices = 0;
    while (n1 > amountOfLeafs) {
        amountOfVertices += amountOfLeafs;
        amountOfLeafs = (amountOfLeafs << 1);
        power++;
    }
    amountOfVertices += amountOfLeafs;
    firstIndex = (1 << (power)) - 1;
    for (int i = 0; i < amountOfVertices; i++) {
        segments.push_back(0);
        sum.push_back(0);
        l1.push_back(0);
        r1.push_back(0);
        d.push_back(-1);
    }

    //showAll("afterCreation");
    vector<string> result;

    for (int i =0 ;i < n; i ++){
        update(start[i],end[i],0,color[i],0,amountOfLeafs);
        //showAll("afterUpdate");
        vector<int> res = trueValue(0,amountOfLeafs);
        result.push_back(std::to_string(res[0])+" "+std::to_string(res[3]));
    }
    //showVector(&result1,"res1");
    //showVector(&result2,"res2");
    for (int i =0; i < n; i++){
        cout << result[i]<<endl;
    }
    return 0;
}
*/
