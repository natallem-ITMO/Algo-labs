

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
    Node *l, *r, *p, *nextInOrder;
    int pri;
    int key;
    int number;

    Node(int this_key, int this_pri, int this_num, Node *next = nullptr, Node *ll = nullptr, Node *rr = nullptr, Node *pp = nullptr) {
        pri = this_pri;
        key = this_key;
        number = this_num;
        nextInOrder = next;
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


bool sortinrev(const Node * a, const Node * b) {
    return (a->key < b->key);
}


int main() {
   // std::ifstream cin("a.in");
   // std::ofstream cout("a.out");
    int n;
    cin >> n;
    vector<Node *> vect;
    int a, b;
    Node * pointerTo1;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        Node * node1 = nullptr;

        vect.push_back(new Node(a,b,i+1, node1));
        if (i != 0) vect[i-1]->nextInOrder = vect[i];
    }
    pointerTo1 = vect[0];
    sort(vect.begin(), vect.end(), sortinrev);
    Node *root = vect[0];
    Node *right = root;
    Node *cur;
    Node *prev;
    for (int i = 1; i < n; i++) {
        Node *newNode = vect[i];
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
    }
    cout << "YES\n";
    do {
        cout << getNum(pointerTo1->p) <<" "<< getNum(pointerTo1 -> l) << " "<<getNum(pointerTo1 -> r)<<endl;
        pointerTo1 = pointerTo1->nextInOrder;
    } while (pointerTo1 != nullptr);


    return 0;
}
*/