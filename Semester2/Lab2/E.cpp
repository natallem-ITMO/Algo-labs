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
    int pri;
    int size = 1;
    int sum = 0;

    Node(int this_pri, int this_sum, Node *ll = nullptr, Node *rr = nullptr) {
        pri = this_pri;
        l = ll;
        r = rr;
        sum = this_sum;
    }
};

int nodeSize(Node *node) {
    if (node == nullptr) return 0;
    else return node->size;
}

int nodeSum(Node *node) {
    if (node == nullptr) return 0;
    else return node->sum;
}

void recalculate(Node *node) {
    node->size = nodeSize(node->l) + nodeSize(node->r);
    node->sum = nodeSum(node->l) + nodeSum(node->r);
}


Node *merge(Node *NL, Node *NR) {
    if (NL == nullptr) return NR;
    else if (NR == nullptr) return NL;
    else {
        if (NL->pri > NR->pri) {
            NL->r = merge(NL->r, NR);
            recalculate(NL);
            return NL;
        }
        NR->l = merge(NL, NR->l);
        recalculate(NR);
        return NR;
    }
}

pair<Node *, Node *> split(int x, Node *&cur) {//элементы <= X в first, >x в second
    if (cur == nullptr) return {nullptr, nullptr};
    int curIndex = nodeSize(cur->l)+1;
    if (x >= curIndex) {
        pair<Node *, Node *> res = split(x-curIndex, cur->r);
        cur->r = res.first;
        recalculate(cur);
        return {cur, res.second};
    } else {
        pair<Node *, Node *> res = split(x, cur->l);
        cur->l = res.second;
        recalculate(cur);
        return {res.first, cur};
    }
}


Node *insert(Node *&cur, int x) {//NB
    if (!exists(cur, x)) {
        pair<Node *, Node *> res = split(x, cur);
     //   srand(time(0));

        return merge(merge(res.first, new Node(x, rand())), res.second);
    } else return cur;
}

Node *remove(Node *&cur, int x) {
    if (cur == nullptr) return nullptr;
    if (cur->key == x) return merge(cur->l, cur->r);
    if (x < cur->key) cur->l = remove(cur->l, x);
    else cur->r = remove(cur->r, x);
    return cur;
}

Node *next(Node *&root, int x) {//return nullptr if not exist else return link to node
    Node *cur = root;
    Node *suc = nullptr;
    while (cur != nullptr) {
        if (cur->key > x) {
            suc = cur;
            cur = cur->l;
        } else {
            cur = cur->r;
        }
    }
    return suc;
}

Node *prev(Node *&root, int x) {//return nullptr if not exist else return link to node
    Node *cur = root;
    Node *suc = nullptr;
    while (cur != nullptr) {
        if (cur->key < x) {
            suc = cur;
            cur = cur->r;
        } else {
            cur = cur->l;
        }
    }
    return suc;
}


int main() {
    //  std::ifstream cin("a.in");
    //  std::ofstream cout("a.out");
    Node *root = nullptr;
    string command;
    Node *res;
    int x;
    while (cin >> command) {
        cin >> x;
        switch (command[0]) {
            case 'i':
                root = insert(root, x);
                break;
            case 'd':
                root = remove(root, x);
                break;
            case 'n':
                res = next(root, x);
                if (res == nullptr) cout << "none" << endl;
                else cout << res->key << endl;
                break;
            case 'p':
                res = prev(root, x);
                if (res == nullptr) cout << "none" << endl;
                else cout << res->key << endl;
                break;
            case 'e':
                if (exists(root, x)) cout << "true" << endl;
                else cout << "false" << endl;
                break;
        }
    }
    return 0;
}

*/
