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
    Node *l, *r;
    long int key;
    long int pri;
    long int amount;

    Node(long int this_key, long int this_pri, Node *ll = nullptr, Node *rr = nullptr, long int lAm = 0, long int rAm = 0) {
        key = this_key;
        pri = this_pri;
        l = ll;
        r = rr;
        amount = lAm + rAm + 1;
    }
};

long int getAmount(Node *node) {
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

pair<Node *, Node *> split(long int x, Node *&cur) {//элементы <= X в first, >x в second
    if (cur == nullptr) return {nullptr, nullptr};
    if (x >= cur->key) {
        pair<Node *, Node *> res = split(x, cur->r);
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

Node *insert(Node *&cur, long int x) {//NB

        pair<Node *, Node *> res = split(x, cur);
        return merge(merge(res.first, new Node(x, rand())), res.second);

}

long int find(Node *cur, long int k) {
    long int rightAmount = getAmount(cur->r);
    if (rightAmount + 1 == k) return cur->key;
    if (rightAmount < k) return find(cur->l, k - rightAmount - 1);
    return find(cur->r, k);
}

Node *remove(Node *cur, long int x) {
    if (cur == nullptr) return nullptr;
    if (cur->key == x) return merge(cur->l, cur->r);
    if (x < cur->key) cur->l = remove(cur->l, x);
    else cur->r = remove(cur->r, x);
    recalc(cur);
    return cur;
}


 int main() {
    long int bugging = 0;
    if (bugging) {
        std::ifstream cin("a.in");
        std::ofstream cout("a.out");


        Node *root = nullptr;

        string command;
        long int x;
        while (cin >> command) {
            cin >> x;
            if (command == "+1" || command == "1") root = insert(root, x);
            else if (command == "-1") root = remove(root, x);
            else cout << find(root, x) << endl;
        }
    } else {
        long int n;
        Node *root = nullptr;
        cin >> n;
        string command;
        long int x;
        for (long int i = 0; i < n; i++) {
            cin >> command >> x;
            if (command == "+1" || command == "1") root = insert(root, x);
            else if (command == "-1") root = remove(root, x);
            else cout << find(root, x) << endl;
        }
    }
    return 0;
}*/