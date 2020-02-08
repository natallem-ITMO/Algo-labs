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
    long long int key;
    long long int pri;
    long long int sum;

    Node(long long int this_key, long long int this_pri, Node *ll = nullptr, Node *rr = nullptr) {
        key = this_key;
        pri = this_pri;
        l = ll;
        r = rr;
        sum = key;
    }
};

long long int getSum(Node *node) {
    if (node == nullptr) return 0;
    return node->sum;
}

void recalc(Node *node) {
    node->sum = getSum(node->l) + getSum(node->r) + node->key;
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

pair<Node *, Node *> split(long long int x, Node *&cur) {//элементы <= X в first, >x в second
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

bool exists(Node *&cur, long long int x) {
    if (cur == nullptr) {
        return false;
    } else {
        if (cur->key == x) return true;
        return exists((x < cur->key) ? cur->l : cur->r, x);
    }
}

Node *insert(Node *&cur, long long int x) {//NB
    if (!exists(cur, x)) {
        pair<Node *, Node *> res = split(x, cur);
        return merge(merge(res.first, new Node(x, rand())), res.second);
    } else return cur;
}

long long int sum(Node *node, long long int A, long long int B) {
    pair<Node *, Node *> splitedLandMR = split(A - 1, node);
    pair<Node *, Node *> splitedMandR = split(B, splitedLandMR.second);
    long long int res = getSum(splitedMandR.first);
    node = merge(splitedLandMR.first, merge(splitedMandR.first, splitedMandR.second));
    return res;
}

 int main() {
    //  std::ifstream cin("a.in");
    //  std::ofstream cout("a.out");
    long long int n;
    const long long int mmm = 1000000000;
    Node *root = nullptr;
    cin >> n;
    char lastRequest = '+';
    long long int lastResult = 0;
    char request;
    long long int x, l, r;
    //   vector<long long int> results;
    for (long long int i = 0; i < n; i++) {
        cin >> request;
        if (request == '+') {
            cin >> x;
            if (lastRequest == '+') root = insert(root, x);
            else root = insert(root, ((lastResult + x) % mmm));
        } else {
            cin >> l >> r;
            lastResult = sum(root, l, r);
            //           results.push_back(lastRequest);
            cout << lastResult << endl;
        }
        lastRequest = request;
    }

    //root = insert(root, 1);
    //long long int res = sum(root, 12,29);

    return 0;
}*/
