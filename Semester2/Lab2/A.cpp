/*#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
using std::vector;
using std::max;
using std::min;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;

struct Node {
    Node *l, *r;
    int key;

    Node(int this_key) {
        key = this_key;
        l = nullptr;
        r = nullptr;
    }
};

void insert(Node *&cur, int x) //Функция добавления звена в дерево
{
    if (cur == nullptr) {
        cur = new Node(x);
    } else {
        if (cur->key == x) return;
        Node *&to = (x < cur->key) ? cur->l : cur->r;
        if (to == nullptr) to = new Node(x);
        else insert(to, x);
    }
}

bool exists(Node *&cur, int x)
{
    if (cur == nullptr) {
        return false;
    } else {
        if (cur->key == x) return true;
        Node *&to = (x < cur->key) ? cur->l : cur->r;
        return exists(to, x);
    }
}

Node *remove(Node *&cur, int x) //Функция добавления звена в дерево
{
    if (cur == nullptr) {
        return cur;
    } else {
        if (x != cur->key) {
            if (x < cur->key) cur->l = remove(cur->l, x);
            else cur->r = remove(cur->r, x);
        } else {
            if (cur->l == nullptr) return cur->r;
            if (cur->r == nullptr) return cur->l;
            Node *y = cur->l;
            Node *py = cur;
            while (y->r != nullptr) {
                py = y;
                y = y->r;
            }
            if (py == cur) cur->l = y->l;
            else py->r = y->l;
            cur->key = y->key;
        }
        return cur;
    }
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
void show(Node *v) {
    if (v == nullptr)
        return;
    show(v->l);
    cout << v->key << " ";
    show(v->r);
}
 int main() {
     std::ifstream cin("a.in");
     std::ofstream cout("a.out");
    Node *root = nullptr;
    vector<string> result;
    string command;
    while (cin >> command){
        //if (command=="g") break;
        Node *res;
        int x;
        //cin >> command;
        cin >> x;
        switch (command[0]){
            case 'i':
                insert(root,x);
                break;
            case 'd':
                root = remove(root,x);
                break;
            case 'n':
                res = next(root,x);
                if (res== nullptr) result.push_back("none");
                else result.push_back(to_string(res->key));
                break;
            case 'p':
                res = prev(root,x);
                if (res== nullptr) result.push_back("none");
                else result.push_back(to_string(res->key));
                break;
            case 'e':
                if (exists(root,x)) result.push_back("true");
                else result.push_back("false");
                break;
        }
    }
    //show(root);
    for (int i = 0; i < result.size(); i ++){
        cout << result[i]<<endl;
    }
    return 0;
}
*/