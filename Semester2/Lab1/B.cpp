#include <iostream>
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

long long int sum(vector<long long int> &vec, int firstIndex, int l, int r) {
    l--;
    r--;
    l += firstIndex;
    r += firstIndex;
    long long int leftRes = 0;
    long long int rightRes = 0;
    while (l < r){
        if (l % 2 ==0) leftRes += vec[l];
        l = l/2;
        if (r % 2 == 1) rightRes += vec[r];
        r = r/2 -1;
    }
    if (l==r) leftRes+=vec[l];
    return leftRes + rightRes;
}

void set(vector<long long int> &vec, int firstIndex, int ind, long long int value) {
    ind--;
    ind = firstIndex + ind;
    vec[ind] = value;
    ind = (ind - 1) / 2;
    while (ind > 0) {
        vec[ind] = (vec[ind * 2 + 1]) + (vec[ind * 2 + 2]);
        //if (ind == 0) break;
        ind = (ind - 1) / 2;
    }
    if (vec.size() != 1){
        vec[ind] = (vec[ind * 2 + 1]) + (vec[ind * 2 + 2]);
    }
}


int main2() {
    //vector<long long int> array;
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
    amountOfVertices+= amountOfLeafs;
    int firstIndex = (1 << (power)) - 1;
   // printf("vertices=%d, leafs=%d, power=%d, firstInd=%d", amountOfVertices, amountOfLeafs, power, firstIndex);

    vector<long long int> array(amountOfVertices, 0);

    for (int i = 0; i < n; i++) {
        cin >> array[firstIndex + i];
    }
    int curIndex = firstIndex - 1;
    while (curIndex >= 0) {
        array[curIndex] = array[curIndex * 2 + 1] + array[curIndex * 2 + 2];
        curIndex--;
    }
    vector<long long int> result;
    string command;

    while (cin >> command) {
        long long int a, b;
        cin >> a >> b;
        if (command == "sum") {
            result.push_back(sum(array, firstIndex, a, b));
        } else if (command== "set"){
            set(array, firstIndex, a, b);
        }
    }
    for (int i =0 ; i < result.size(); i++){
        cout << result[i]<< endl;
    }
    return 0;
}

