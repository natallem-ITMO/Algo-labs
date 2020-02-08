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
    Node *l, *r, *p;
    int pri;
    int amount;
    int inf;


    bool cycled;

    Node(int pri, int inf, Node *p = nullptr, Node *l = nullptr, Node *r = nullptr, int lAm = 0,
         int rAm = 0, bool cycled = false) : pri(pri), inf(inf), l(l), r(r),
                                             amount(lAm + rAm + 1), cycled(cycled) {
        this->p = p;
        if (p == nullptr) this->p = this;
    }
};

void setParent(Node *node, Node *per) {
    if (node != nullptr) node->p = per;
}



int getAmount(Node *node) {
     if (node == nullptr) return 0;
    return node->amount;
}

void recalc(Node *node) {

    node->amount = getAmount(node->l) + getAmount(node->r) + 1;
}

Node *merge(Node *NL, Node *NR) {
    if (NL == nullptr) return NR;
    else if (NR == nullptr) return NL;
    else {
        if (NL->pri > NR->pri) {
            Node *mergeR = merge(NL->r, NR);
            NL->r = mergeR;
            setParent(mergeR, NL);
            recalc(NL);
            return NL;
        }
        Node *mergeL = merge(NL, NR->l);
        setParent(mergeL, NR);
        NR->l = mergeL;
        recalc(NR);
        return NR;
    }
}

Node *getRoot(Node *node) {
    while (node->p != node) node = node->p;
    return node;
}

bool isCycled(Node *node) {
    return getRoot(node)->cycled;
}

pair<Node *, Node *> split(int x, Node *&cur) {//элементы с индексом <= X в first, >x в second

    if (cur == nullptr) return {nullptr, nullptr};

    int leftAmount = getAmount(cur->l);
    if (x >= leftAmount + 1) {
        pair<Node *, Node *> res = split(x - leftAmount - 1, cur->r);
        cur->r = res.first;
        setParent(res.first, cur);
        recalc(cur);
        setParent(res.second, res.second);
        return {cur, res.second};
    } else {
        pair<Node *, Node *> res = split(x, cur->l);
        cur->l = res.second;
        setParent(res.second, cur);
        recalc(cur);
        setParent(res.first, res.first);
        return {res.first, cur};
    }
}

Node *getNodeByIndex(Node *node, int index) {
    node = getRoot(node);
    pair<Node *, Node *> AX_Y = split(index, node);
    pair<Node *, Node *> A_X_Y = split(index - 1, AX_Y.first);
    node = A_X_Y.second;
    merge(merge(A_X_Y.first, A_X_Y.second), AX_Y.second);
    return node;
}


void showNode(Node *cur) {
    if (cur == nullptr)
        return;
    showNode(cur->l);
    cout << cur->inf << " ";
    showNode(cur->r);
}

void show(Node *cur, string s = "", int x = -2, int y = -2) {
    // cout << s;
    // printf(" %d %d: ", x, y);
    // showNode(cur);
    // cout << endl;
}

int getIndex1(Node *node, Node *prevNode) {

    if (node == prevNode)
        return 0;
    int leftSum = 0;
    if (prevNode == node->r) {
        leftSum = getAmount(node->l) + 1;
    }
    leftSum += getIndex1(node->p, node);
    return leftSum;
}

int getIndex(Node *node) {
    return getAmount(node->l) + 1 + getIndex1(node->p, node);
}

Node *shiftLeft(int k, Node *node) {
    pair<Node *, Node *> pp = split(k, node);
    return merge(pp.second, pp.first);
}

void reverse(Node * node){
    if (node == nullptr) return;
    Node * t = node-> l;
    node->l = node->r;
    node-> r = t;
    reverse(node->l);
    reverse(node->r);
}

void addPath(int x, int y, vector<Node *> &vec) {
    Node *nodeX = vec[x - 1];
    Node *rootX = getRoot(nodeX);
    Node *nodeY = vec[y - 1];
    Node *rootY = getRoot(nodeY);
    show(rootX, "rootX before added", x, y);
    show(rootY, "rootY before added", x, y);
    if (rootX != rootY) {
        int indX = getIndex(nodeX);
        int indY = getIndex(nodeY);
        if (indX != 1 && indY != 1) {
            reverse(rootY);
            merge(rootX, rootY);
        } else if (indX == 1 && indY == 1) {
            reverse(rootX);
            merge(rootX, rootY);
        } else if (indX == 1) {
            merge(rootY, rootX);
        } else merge(rootX, rootY);
    } else rootX->cycled = true;
    rootX = getRoot(nodeX);
    string s = "cycled " + to_string(rootX->cycled) + " after added";

    //show(rootX,s, x,y);
}

void removePath(int x, int y, vector<Node *> &vec) {

    Node *nodeX = vec[x - 1];
    Node *rootX = getRoot(nodeX);
    Node *nodeY = vec[y - 1];
    Node *rootY = getRoot(nodeY);

    if (rootX != rootY) return;
    show(rootX, "before remove path", x, y);
    int indX = getIndex(nodeX);
    int indY = getIndex(nodeY);
    if (rootX->cycled == true) {
        rootX->cycled = false;
        if (min(indX, indY) == 1 && max(indX, indY) == getAmount(rootX)) {
            show(rootX, "remove path in cycle no need", x, y);
            return;
        }
        shiftLeft(min(indX, indY), rootX);
        show(getRoot(rootX), "remove path in cycle", x, y);
    } else {
        if (abs(indX - indY) != 1) return;
        split(min(indX, indY), rootX);
        show(getRoot(nodeX), "remove path rootX", x, y);
        show(getRoot(nodeY), "remove path rootY", x, y);
    }
}

int getAns(int x, int y, vector<Node *> &vec) {
    int result;
    if (x == y) {
        result = 0;
    } else {
        Node *nodeX = vec[x - 1];
        Node *rootX = getRoot(nodeX);
        Node *nodeY = vec[y - 1];
        Node *rootY = getRoot(nodeY);
        if (rootX != rootY) {
            result = -1;
        } else {
            int indX = getIndex(nodeX);
            int indY = getIndex(nodeY);
            if (indX > indY) swap(indX, indY);
            result = indY - indX - 1;
            if (rootX->cycled) {
                int res2 = getAmount(rootX) - indY + indX - 1;
                result = min(res2, result);
            }
        }
    }
    // printf("ans %d %d res=%d \n", x, y, result);
    return result;
}

int main() {
    //std::ifstream cin("a.in");
    // std::ofstream cout("a.out");

    int n, m, q;
    cin >> n >> m >> q;

    vector<Node *> vec;
    for (int i = 1; i <= n; i++) {
        vec.push_back(new Node(rand(), i));
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        addPath(x, y, vec);
    }
    for (int i = 0; i < q; i++) {
        char command;
        int x, y;
        cin >> command >> x >> y;
        switch (command) {
            case '?':
                cout << getAns(x, y, vec) << endl;
                break;
            case '-':
                removePath(x, y, vec);
                break;
            case '+':
                addPath(x, y, vec);
                break;
        }
    }
    return 0;
}*/
