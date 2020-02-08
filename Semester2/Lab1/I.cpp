/*

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int amount;
const int noIncline = INT32_MIN;

struct Node {
    int maximum, last, incline, indFirst, indLast;
    Node *l, *r, *parent;
};


void insert(Node *&current) //Функция добавления звена в дерево
{
    if (nullptr == current) {
        current = new Node;
        current->l = current->r = nullptr;
        current->maximum = current->last = current->incline = current->indFirst = 0;
        current->indLast = amount;
        current->parent = nullptr;
    }
    if (current->indLast - current->indFirst <= 1)
        return;
    if (current->l != nullptr)
        return;
    current->l = new Node;
    current->r = new Node;
    int incline = current->incline;
    int start = current->indFirst;
    int end = current->indLast;
    int med = (start + end) / 2;
    current->l->indFirst = start;
    current->l->indLast = current->r->indFirst = med;
    current->r->indLast = end;
    current->l->maximum = current->r->maximum = current->r->last = current->l->last = (med - start) * incline;
    current->l->incline = current->r->incline = incline;
    current->incline = noIncline;
    current->r->l = current->r->r = current->l->r = current->l->l = nullptr;
    current->l->parent = current->r->parent = current;
}

void push(Node *&node) {
    if (node->l != nullptr) {
        if (node->incline != noIncline) {
            node->l->incline = node->incline;
            node->r->incline = node->incline;
            node->incline = noIncline;
        }
    }
}

vector<int> trueValue(Node *&node) {//NB
    if (node->incline == noIncline) {
        return {node->maximum, node->last};
    } else {
        int res = (node->indLast - node->indFirst) * node->incline;
        return {res, res};
    }
}

void updateNode(Node *&node) {
    vector<int> leftTrueValue = trueValue(node->l);
    vector<int> rightTrueValue = trueValue(node->r);
    node->maximum = max(leftTrueValue[0], (leftTrueValue[1] + rightTrueValue[0]));
    node->last = leftTrueValue[1] + rightTrueValue[1];
}

void set(Node *&node, int l, int r, int value) {
    if (node->indFirst >= r || node->indLast <= l) return;
    if (node->indFirst >= l && node->indLast <= r) {
        node->incline = value;
        return;
    }
    if (node->l == nullptr) insert(node);
    push(node);
    set(node->l, l, r, value);
    set(node->r, l, r, value);
    updateNode(node);
}

int getAns(Node *&node, int d) {
    if (node->parent == nullptr && trueValue(node)[0] <= d) return amount + 1;
    if (node->indLast - node->indFirst == 1) {
        return node->indFirst;
    }

    if (node->l == nullptr) insert(node);
    push(node);
    updateNode(node);
    vector<int> leftRes = trueValue(node->l);
    if (leftRes[0] > d) return getAns(node->l, d);
    else {
        vector<int> rightRes = trueValue(node->r);
        return getAns(node->r, d - leftRes[1]);
    }

}


void show(Node *&Tree) {
    if (Tree != nullptr) {
        show(Tree->l);
        printf(" [%d %d] ", Tree->indFirst, Tree->indLast);
        show(Tree->r);
    }
}

int main() {
    int n;
    cin >> n;
    int amountOfLeafs = 1;
    int power = 0;
    while (n > amountOfLeafs) {
        amountOfLeafs = (amountOfLeafs << 1);
        power++;
    }
    //printf("vertices=%d, leafs=%d, power=%d, firstInd=%d", amountOfVertices, amountOfLeafs, power, firstIndex);
    amount = amountOfLeafs;
    Node *root = nullptr;
    insert(root);
    string command;
    cin >> command;
    vector<int> results;

    */
/*results.push_back(getAns(root, 1));
    set(root, 0, 4, 2);
    results.push_back(getAns(root, 3));
    results.push_back(getAns(root, 1));
    set(root, 2 - 1, 2, -1);
    results.push_back(getAns(root, 3));*//*



    while (command != "E") {
        if (command == "Q") {
            int d;
            cin >> d;
            int ans = getAns(root, d);
            if (ans > n) results.push_back(n);
            else results.push_back(ans);
        }
        if (command == "I") {
            int a, b, D;
            cin >> a >> b >> D;
            set(root, a - 1, b, D);
        }
        cin >> command;
    }
    for (int i : results) {
        cout << i << endl;
    }


    */
/*set(root,0,3,5);
    set(root,2,5,1);
    set(root,5,8,-2);
    //printf("%d %d %d", getAns(root,5),getAns(root,12), getAns(root,17));

   // add_children(Tree->l);
    show(root);*//*

    return 0;
}*/
