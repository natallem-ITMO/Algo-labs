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

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using namespace std;



struct Node {

    int key;
    int cost;
    Node *l, *r;
    Node *next;
    int plus;
    int pri;



    void setNextMyself(Node *cur) {
        cur->next = cur;
    }

    Node(int this_key, int this_pri, int cconst, Node *nnext = nullptr, Node *ll = nullptr, Node *rr = nullptr, int pplus = 0) {
        key = this_key;
        pri = this_pri;
        cost  = cconst;
        l = ll;
        r = rr;
        if (nnext == nullptr) next = this;
        else next = nnext;
        plus = pplus;
    }
};

void setPlus(Node *node, int curPlus) {
    if (node != nullptr) node->plus += curPlus;
}

void push(Node *node) {
    if (node == nullptr) return;
    node->key += node->plus;
    setPlus(node->l, node->plus);
    setPlus(node->r, node->plus);
    node->plus = 0;
}

void pushEnds(Node *node) {
    Node *curRight = node;
    Node *curLeft = node;
    while (curRight != nullptr) {
        push(curRight);
        curRight = curRight->r;
    }
    while (curLeft != nullptr) {
        push(curLeft);
        curLeft = curLeft->l;
    }
}

Node *merge(Node *NL, Node *NR) {
    push(NL);
    push(NR);
    if (NL == nullptr) return NR;
    else if (NR == nullptr) return NL;
    else {
        if (NL->pri > NR->pri) {
            NL->r = merge(NL->r, NR);
            return NL;
        }
        NR->l = merge(NL, NR->l);
        return NR;
    }
}

pair<Node *, Node *> split(int x, Node *cur) {//элементы <= X в first, >x в second
    push(cur);
    if (cur == nullptr) return {nullptr, nullptr};
    if (x >= cur->key) {
        pair<Node *, Node *> res = split(x, cur->r);
        cur->r = res.first;
        return {cur, res.second};
    } else {
        pair<Node *, Node *> res = split(x, cur->l);
        cur->l = res.second;
        return {res.first, cur};
    }
}

Node *find(Node *cur, int x) {
    push(cur);
    if (cur == nullptr) {
        return nullptr;
    } else {
        if (cur->key == x) return cur;
        return find((x < cur->key) ? cur->l : cur->r, x);
    }
}

Node *insert(Node *cur, int x, int cost) {//NB
    Node *next = find(cur, x + 1);
    Node *prev = find(cur, x - 1);
    pair<Node *, Node *> res = split(x, cur);
    Node *newNode;
    if (next != nullptr) newNode = new Node(x, rand(), cost, next);
    else newNode = new Node(x, rand(), cost);
    if (prev != nullptr) prev->next = newNode;
    cur = merge(merge(res.first, newNode), res.second);
    return cur;
}

Node *getNext(Node *node) {
    if (node->next == node)
        return node;
    node->next = getNext(node->next);
    return node->next;
}

Node *insertWithShift(Node *root, int x, int cost) {//NB
    Node *shift = find(root, x);
    if (shift == nullptr)
        return insert(root, x, cost);
    Node *prevShift = find(root, x - 1);
    Node *nextShift = getNext(shift);
    Node * conjShift = find(root, nextShift->key + 2);
    if (conjShift != nullptr) nextShift->next = conjShift;
    pair<Node *, Node *> F_ML = split(x - 1, root);
    pair<Node *, Node *> M_L = split(nextShift->key, F_ML.second);
    M_L.first->plus += 1;
    pushEnds(M_L.first);
    Node *addedNode = new Node(x, rand(),cost, shift);
    root = merge(merge(merge(F_ML.first, addedNode), M_L.first), M_L.second);
    if (prevShift != nullptr) prevShift-> next = addedNode;
    return root;
}
void showAll(Node * node, int *lastPrinted){

    push(node);
    if (node == nullptr) return;
    showAll(node->l,  lastPrinted);
   // if (node-> key == 10 ) cout << "FUCK";
    int curInd = node->key;
    for (int i = *lastPrinted + 1; i < curInd; i ++){
        cout << 0 << " ";
    }
    cout << node-> cost << " ";
    *lastPrinted = curInd;
    showAll(node->r,  lastPrinted);

}

int findLast(Node * node){
    if (node->r == nullptr) return node->key;
    findLast(node->r);
}


int main() {
    int debug = 0;
    if (debug){
        std::ifstream cin("a.in");
        std::ofstream cout("a.out");
        int n, m;
        Node *root = nullptr;
        cin >> n >> m;
        int i = 0;
        while (cin >> m) root = insertWithShift(root, m, ++i);

        cout << findLast(root) << endl;
        int xxx = 0;
        Node * f = find(root, 10);
        int x = 0;
        showAll(root, &x);

        f = find(root, 10);
        int xx =1;

    } else {

       // std::ifstream cin("a.in");
        //    std::ofstream cout("a.out");
        int n, m;
        Node *root = nullptr;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> m;
            root = insertWithShift(root, m, i + 1);
        }
        cout << findLast(root) << endl;
        int x = 0;
        showAll(root, &x);
    }


    return 0;
}*/
