

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


int xFail = 0;
int yFail = 0;

int getCharNum(char c) {
    return c - 'a';
}

struct Node {
    char c;
    int charAmount;
    int mask;
    int amount;
    Node *l, *r;
    int pri;
    int charNum;

    Node(int pri, int c, int charAmount) : pri(pri), c(c), charAmount(charAmount) {
        charNum = getCharNum(c);
        l = nullptr;
        r = nullptr;
        amount = charAmount;
        mask = 1 << charNum;
    }
};

int getAmount(Node *node) {
    if (node == nullptr) return 0;
    return node->amount;
}

int getMask(Node *node) {
    if (node == nullptr) return 0;
    else return node->mask;
}

void recalc(Node *node) {
    node->amount = getAmount(node->l) + getAmount(node->r) + node->charAmount;
    node->mask = getMask(node->l) | getMask(node->r) | (1 << node->charNum);
}

Node *merge(Node *NL, Node *NR) {
    if (NL == nullptr) return NR;
    else if (NR == nullptr) return NL;
    else {
        if (NL->pri > NR->pri) {
            Node *mergeR = merge(NL->r, NR);
            NL->r = mergeR;
            recalc(NL);
            return NL;
        }
        Node *mergeL = merge(NL, NR->l);
        NR->l = mergeL;
        recalc(NR);
        return NR;
    }
}

pair<Node *, Node *> split(int x, Node *cur) {//элементы с индексом <= X в first, >x в second
    if (cur == nullptr) return {nullptr, nullptr};
    int leftAmount = getAmount(cur->l);
    int curAmount = cur->charAmount;
    if (x > leftAmount + curAmount) {
        pair<Node *, Node *> res = split(x - leftAmount - curAmount, cur->r);
        cur->r = res.first;
        recalc(cur);
        return {cur, res.second};
    }
    if (x <= leftAmount) {
        pair<Node *, Node *> res = split(x, cur->l);
        cur->l = res.second;
        recalc(cur);
        return {res.first, cur};
    }
    if (x == leftAmount + curAmount) {
        Node *rr = cur->r;
        cur->r = nullptr;
        recalc(cur);
        return {cur, rr};
    }

    Node *ll = cur->l;
    int amountInLeftSide = x - leftAmount;
    Node *newL = new Node(rand(), cur->c, amountInLeftSide);
    newL->l = ll;
    recalc(newL);
    cur->l = nullptr;
    cur->charAmount -= amountInLeftSide;
    recalc(cur);
    return {newL, cur};
}

pair<Node *, Node *> splitForQueryXInRight(int x, Node *cur) {//элементы с индексом <= X в first, >x в second
    if (cur == nullptr) return {nullptr, nullptr};
    int leftAmount = getAmount(cur->l);
    int curAmount = cur->charAmount;
    if (x > leftAmount + curAmount) {
        pair<Node *, Node *> res = splitForQueryXInRight(x - leftAmount - curAmount, cur->r);
        cur->r = res.first;
        recalc(cur);
        return {cur, res.second};
    }
    if (x <= leftAmount) {
        pair<Node *, Node *> res = splitForQueryXInRight(x, cur->l);
        cur->l = res.second;
        recalc(cur);
        return {res.first, cur};
    }
    Node *ll = cur->l;
    cur->l = nullptr;
    recalc(cur);
    return {ll, cur};
}

pair<Node *, Node *> splitForQueryXInLeft(int x, Node *cur) {//элементы с индексом <= X в first, >x в second
    if (cur == nullptr) return {nullptr, nullptr};
    int leftAmount = getAmount(cur->l);
    int curAmount = cur->charAmount;
    if (x > leftAmount + curAmount) {
        pair<Node *, Node *> res = splitForQueryXInLeft(x - leftAmount - curAmount, cur->r);
        cur->r = res.first;
        recalc(cur);
        return {cur, res.second};
    }
    if (x <= leftAmount) {
        pair<Node *, Node *> res = splitForQueryXInLeft(x, cur->l);
        cur->l = res.second;
        recalc(cur);
        return {res.first, cur};
    }
    Node *rr = cur->r;
    cur->r = nullptr;
    recalc(cur);
    return {cur, rr};

}

Node *insert(Node *root, int index, int number, char let) {
    index--;
    pair<Node *, Node *> sp = split(index, root);
    Node *nnode = new Node(rand(), let, number);
    root = merge(merge(sp.first, nnode), sp.second);
    return root;
}

Node *remove(Node *root, int index, int number) {
    index--;
    int indexLeft = index + number;
    pair<Node *, Node *> XY_Z = split(indexLeft, root);
    pair<Node *, Node *> X_Y_Z = split(index, XY_Z.first);
    root = merge(X_Y_Z.first, XY_Z.second);
    return root;
}

void showSmall(Node *cur) {
    //std::ofstream cout("a.out");
    if (cur == nullptr)
        return;
    showSmall(cur->l);
    printf("%c(%d) ", cur->c, cur->charAmount);

    showSmall(cur->r);
}

void showAll(Node *cur) {
    //std::ofstream cout("a.out");
    if (cur == nullptr)
        return;
    showAll(cur->l);
    for (int i = 0; i < cur->charAmount; i++) {
        cout << cur->c << ' ';
    }
    showAll(cur->r);
}

void show(Node *cur, string s = "") {
    cout << endl << s << endl;
    showAll(cur);
    cout << endl;
    showSmall(cur);

}


int countBits(int mask) {
    int res = 0;
    int pointer = 1;
    for (int i = 0; i < 26; i++) {
        if ((pointer & mask) > 0) ++res;
        pointer <<= 1;
    }
    return res;
}

pair<Node *, Node *> getFirstNode(Node *root) {
    if (root == nullptr)
        return {nullptr, nullptr};
    Node *cur = root;

    while (cur->l != nullptr) cur = cur->l;
    return split(cur->charAmount, root);
}

pair<Node *, Node *> getLastNode(Node *root) {
    if (root == nullptr)
        return {nullptr, nullptr};
    Node *cur = root;
    while (cur->r != nullptr) cur = cur->r;
    return split(root->amount - cur->charAmount, root);
}

pair<int, Node *> query(Node *root, int ind1, int ind2) {
    bool bag = 0;
    //if (ind1 == xFail && ind2 == yFail) bag = 1;
    // bag = 0;
    if (bag) {
        show(root);
        printf("\nin query %d %d \n", ind1, ind2);
        pair<Node *, Node *> XY_Z = splitForQueryXInLeft(ind2, root);
        printf("XY_Z\n");
        show(XY_Z.first);
        cout << endl;
        show(XY_Z.second);
        cout << endl;
        pair<Node *, Node *> X_Y_Z = splitForQueryXInRight(ind1, XY_Z.first);
        printf("X_Y_Z\n");
        show(X_Y_Z.first);
        cout << endl;
        show(X_Y_Z.second);
        cout << endl;
        int result = countBits(X_Y_Z.second->mask);
        //printf("%d ", X_Y_Z.second->mask);
        root = merge(merge(X_Y_Z.first, X_Y_Z.second), XY_Z.second);
        return {result, root};
    } else {

        pair<Node *, Node *> XY_Z = splitForQueryXInLeft(ind2, root);

        pair<Node *, Node *> X_Y_Z = splitForQueryXInRight(ind1, XY_Z.first);

        int result = countBits(X_Y_Z.second->mask);

        root = merge(merge(X_Y_Z.first, X_Y_Z.second), XY_Z.second);
        return {result, root};
    }

}


int main() {
    bool bug = 0;
    if (bug) {
        std::ifstream cin("a.in");
        // std::ofstream cout("a.out");
        Node *root = nullptr;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            char com, ch;
            int x, y;
            cin >> com >> x >> y;
            switch (com) {
                case '+':
                    cin >> ch;
                    root = insert(root, x, y, ch);
                    show(root);
                    printf(" --- + %d %d %c\n", x, y, ch);
                    break;
                case '-':
                    root = remove(root, x, y);
                    show(root);
                    printf("--- - %d %d\n", x, y);
                    break;
                case '?':
                    show(root);
                    pair<int, Node *> req = query(root, x, y);
                    root = req.second;
                    printf(" --- req %d %d = %d\n", x, y, req.first);
                    break;
            }
        }
        pair<Node *, Node *> pp = getFirstNode(root);
        show(pp.first, "this is splitted first");
        show(pp.second, "this is splitted second");
        pair<Node *, Node *> pp1 = getLastNode(root);
        show(pp1.first, "this is splitted first");
        show(pp1.second, "this is splitted second");

        //show(root);
    } else {
        // std::ifstream cin("a.in");
        //  std::ofstream cout("a.out");
        Node *root = nullptr;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            char com, ch;
            int x, y;
            cin >> com >> x >> y;
            switch (com) {
                case '+':
                    cin >> ch;
                    root = insert(root, x, y, ch);

                    break;
                case '-':
                    root = remove(root, x, y);

                    break;
                case '?':
                    // show(root);
                    pair<int, Node *> req = query(root, x, y);
                    root = req.second;
                    cout << req.first << endl;
                    //printf(" --- req %d %d = %d\n", x, y, req.first);
                    break;
            }
        }
    }

    return 0;
}