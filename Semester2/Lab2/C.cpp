/*



#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <algorithm>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using namespace std;
const int MIN = -10000000;

struct Node {
    Node *l, *r, *p;
    int pri;
    int key;
    int number;

    Node(int this_key, int this_pri, int this_num, Node *ll = nullptr, Node *rr = nullptr, Node *pp = nullptr) {
        pri = this_pri;
        key = this_key;
        number = this_num;
        l = ll;
        r = rr;
        p = pp;
    }
};

int getPri(Node *node) {
    if (node == nullptr) return MIN;
    else return node->pri;
}

int getNum(Node *node) {
    if (node == nullptr) return 0;
    else return node->number;
}


bool sortinrev(const vector<int> &a, const vector<int> &b) {
    return (a[0] < b[0]);
}


int main() {
    std::ifstream cin("a.in");
    std::ofstream cout("a.out");
    int n;
    cin >> n;
    vector<vector<int> > vect;
    vector<Node *> result(n + 1);
    int a, b;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        vect.push_back({a, b, i + 1});

    }
    sort(vect.begin(), vect.end(), sortinrev);
    Node *root = new Node(vect[0][0], vect[0][1], vect[0][2]);
    Node *right = root;
    Node *cur;
    Node *prev;
    result[vect[0][2]] = root;
    for (int i = 1; i < n; i++) {
        Node *newNode = new Node(vect[i][0], vect[i][1], vect[i][2]);
        cur = right;
        if (cur->pri < newNode->pri) {
            cur->r = newNode;
            newNode->p = cur;
        } else {
            prev = cur;
            cur = cur->p;
            while (getPri(cur) > newNode->pri) {
                prev = cur;
                cur = cur->p;
            }
            newNode->l = prev;
            prev->p = newNode;
            if (cur != nullptr) {
                cur->r = newNode;
                newNode->p = cur;
            }
        }
        right = newNode;
        result[vect[i][2]] = newNode;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cur = result[i + 1];
        cout << getNum(cur->p) << " " << getNum(cur->l) << " " << getNum(cur->r) << endl;

    }

    return 0;
}*/
