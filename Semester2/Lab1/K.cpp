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
int firstIndex;
int lastIndex;

int getRs(int node) {
    return node * 2 + 2;
}

int getLs(int node) {
    return getRs(node) - 1;
}
int getPer(int node) {
    return (node-1)/2;
}

void update(vector<int> &vec, int node){
    node = getPer(node);
    while(node >= 0){
        if (node==0){
            if  (vec[getLs(node)] == 0 || vec[getRs(node)]==0) vec[node]=0;
            else vec[node] = 1;
            break;
        }
        if  (vec[getLs(node)] == 0 || vec[getRs(node)]==0) vec[node]=0;
        else vec[node] = 1;
        node = getPer(node);

    }
}

void set(vector<int> &vec, int node, int value){
    vec[node] = value;
    update(vec,node);
}

int find(vector<int> &vec, int index, int node, int L, int R){
    if (vec[node]==1) return -1;
    if (index>=R) return -1;
    if (R-L==1) return node;
    int m = (R+L)/2;
    int left = find(vec,index,getLs(node), L,m);
    if (left==-1) left = find(vec,index,getRs(node), m,R);
    return left;
}

int main() {

    std::ifstream fin("parking.in");
    std::ofstream fout("parking.out");

    int n;
    int m;
    fin >> n>>m;

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
    vector<int> vec(amountOfVertices, 1);

    for (int i = firstIndex; i <= lastIndex; i++) {
        vec[i] = 0;
    }
    for (int i = firstIndex-1; i >= 0; i --){
        if (vec[getLs(i)] == 0 || vec[getRs(i)]==0) vec[i]=0;
    }
    string command;
    int ind;
    vector<int> res;
    for (int i = 0;i < m; i++){
        fin >> command >> ind;
        //ind +=(firstIndex-1);
        if (command=="enter"){
            int posInd = find(vec,ind-1,0, 0, amountOfLeafs);

            if (posInd==-1) {
                posInd = find(vec,0,0,0,amountOfLeafs);
            }
            set(vec,posInd,1);
            posInd  = posInd - firstIndex;
            res.push_back(posInd+1);
           // set(vec,posInd,1);
        }
        else {
            ind +=(firstIndex-1);
            set(vec,ind,0);
        }
    }
    for (int i : res){
        fout<<i<<endl;
       //printf("%d\n", i);
    }

    return 0;
}
*/



