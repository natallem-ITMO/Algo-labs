
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
    Node *l, *r;
    int pri;
    int amount;
    int inf;

    Node(int this_pri, int inf1, Node *ll = nullptr, Node *rr = nullptr, int lAm = 0, int rAm = 0) {
        pri = this_pri;
        inf = inf1;
        l = ll;
        r = rr;
        amount = lAm + rAm + 1;
    }
};

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
            NL->r = merge(NL->r, NR);
            recalc(NL);
            return NL;
        }
        NR->l = merge(NL, NR->l);
        recalc(NR);
        return NR;
    }
}

pair<Node *, Node *> split(int x, Node *&cur) {//элементы с индексом <= X в first, >x в second
    if (cur == nullptr) return {nullptr, nullptr};
    int leftAmount = getAmount(cur->l);
    if (x >= leftAmount + 1) {
        pair<Node *, Node *> res = split(x - leftAmount - 1, cur->r);
        cur->r = res.first;
        recalc(cur);
        return {cur, res.second};
    } else {
        pair<Node *, Node *> res = split(x, cur->l);
        cur->l = res.second;
        recalc(cur);
        return {res.first, cur};
    }
}

Node *toBegin(Node *cur, int l, int r) {
    pair<Node *, Node *> FM_L = split(r, cur);
    pair<Node *, Node *> F_M = split(l - 1, FM_L.first);
    cur = merge(F_M.second, F_M.first);
    cur = merge(cur, FM_L.second);
    return cur;
}

Node *insertToStart(Node *cur, int x) {//NB
    pair<Node *, Node *> res = split(0, cur);
    Node *toRet = merge(merge(res.first, new Node(rand(), x)), res.second);
    return toRet;
}

Node *insertToEnd(Node *cur, int x) {//NB
    Node *toRet = merge(cur, new Node(rand(), x));
    return toRet;
}

void show(Node *cur) {//NB
    int amount = getAmount(cur);
    pair<Node *, Node *> pa;
    for (int i = 0; i < amount; i++) {
        pa = split(1, cur);
        cout << pa.first->inf << " ";
        cur = pa.second;
    }
}





int main() {
    int bugging = 0;
    if (bugging) {
        Node *root = nullptr;
        root = insertToEnd(root, 1);
        root = insertToEnd(root, 2);
        root = insertToEnd(root, 3);
        root = insertToEnd(root, 4);
        root = insertToEnd(root, 5);
        root = insertToEnd(root, 6);
        root = toBegin(root, 2, 4);
        root = toBegin(root, 3, 4);
        int x = 5;
        show(root);
        x++;

    } else {
        int n, m;
        Node *root = nullptr;

        cin >> n >> m;
        int l, r;
        for (int i = 1; i <= n; i++) {
            root = insertToEnd(root, i);
        }
        for (int i = 0; i < m; i++) {
            cin >> l >> r;
            root = toBegin(root, l, r);
        }
        show(root);

    }
    return 0;
}