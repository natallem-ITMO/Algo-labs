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
    int key;
    int pri;

    Node(int this_key, int this_pri, Node *ll = nullptr, Node *rr = nullptr) {
        key = this_key;
        pri = this_pri;
        l = ll;
        r = rr;
    }
};

Node *merge(Node *NL, Node *NR) {
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

pair<Node *, Node *> split(int x, Node *&cur) {
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

bool exists(Node *&cur, int x) {
    if (cur == nullptr) {
        return false;
    } else {
        if (cur->key == x) return true;
        return exists((x < cur->key) ? cur->l : cur->r, x);
    }
}

Node *insert(Node *&cur, int x) {//NB
    if (!exists(cur, x)) {
        pair<Node *, Node *> res = split(x, cur);
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
