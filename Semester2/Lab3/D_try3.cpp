//#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <set>

using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

struct Node {
    int inf;

    Node *left;
    Node *right;
    Node *parent;
    int sum;
    Node *link;
    Node * alive_acs;
    bool alive;
    Node * real_parent;
//    set<int> childrens;
    explicit Node(int inf) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        sum = 1;
        this->inf = inf;
        alive = true;
        alive_acs = this;
        link = nullptr;
        real_parent = nullptr;
    }
    ~Node() {
        delete left;
        delete right;
    }
};

int get_sum(Node *x) {
    if (x == nullptr) return 0;
    else return x->sum;
}

void recalc(Node *node) {
    if (node != nullptr)
        node->sum = get_sum(node->left) + get_sum(node->right) + 1;
}

void set_parent(Node *son, Node *parent) {
    if (son == nullptr) return;
    son->parent = parent;
}

//class Splay_tree {
void zig(Node *x) {
    Node *p = x->parent;

    if (p->left == x) {
        Node *b = x->right;
        x->right = p;
        p->left = b;
        if (b != nullptr) b->parent = p;

    } else {
        Node *b = x->left;
        x->left = p;
        p->right = b;
        if (b != nullptr) b->parent = p;
    }
    recalc(p);
    recalc(x);
    x->parent = nullptr;
    p->parent = x;
}

void zig_zig(Node *x) {
    Node *p = x->parent;
    Node *g = p->parent;

    if (p->left == x) {
        Node *b = x->right;
        Node *c = p->right;

        x->parent = g->parent;
        x->right = p;

        p->parent = x;
        p->left = b;
        p->right = g;

        g->parent = p;
        g->left = c;

        if (b != nullptr) b->parent = p;
        if (c != nullptr) c->parent = g;

        if (x->parent != nullptr) {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }
    } else {
        Node *b = p->left;
        Node *c = x->left;

        x->parent = g->parent;
        x->left = p;

        p->parent = x;
        p->left = g;
        p->right = c;

        g->parent = p;
        g->right = b;

        if (b != nullptr) b->parent = g;
        if (c != nullptr) c->parent = p;

        if (x->parent != nullptr) {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }
    }
    recalc(g);
    recalc(p);
    recalc(x);
}

void zig_zag(Node *x) {
    Node *p = x->parent;
    Node *g = p->parent;

    if (p->right == x) {
        Node *b = x->left;
        Node *c = x->right;

        x->left = p;
        x->right = g;
        x->parent = g->parent;

        p->right = b;
        p->parent = x;

        g->left = c;
        g->parent = x;


        if (b != nullptr) b->parent = p;
        if (c != nullptr) c->parent = g;

        if (x->parent != nullptr) {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }
    } else {
        Node *b = x->left;
        Node *c = x->right;

        x->left = g;
        x->right = p;
        x->parent = g->parent;

        p->left = c;
        p->parent = x;

        g->right = b;
        g->parent = x;

        if (b != nullptr) b->parent = g;
        if (c != nullptr) c->parent = p;

        if (x->parent != nullptr) {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }
    }
    recalc(g);
    recalc(p);
    recalc(x);
}


Node *splay(Node *x) {
    while (x->parent != nullptr) {
        Node *p = x->parent;
        Node *g = p->parent;

        if (g == nullptr) {
            zig(x);
        } else {
            if ((g->left == p && p->left == x) || (g->right == p && p->right == x)) zig_zig(x);
            else zig_zag(x);
        }
    }
    return x;
}

Node *find_easy(Node *cur_node, int ind) {
    if (cur_node == nullptr)
        return nullptr;
    int sum_left = get_sum(cur_node->left);
    if (sum_left + 1 == ind) {
        return cur_node;
    } else if (sum_left >= ind) {
        return find_easy(cur_node->left, ind);
    } else {
//            Node *new_node = find_easy(cur_node->right, ind - sum_left - 1);
//            if (new_node == nullptr) return cur_node;
//            return new_node;
        return find_easy(cur_node->right, ind - sum_left - 1);

    }
}

void show_node(Node *root) {
    if (root != nullptr) {
        show_node(root->left);
        cout << root->inf << " ";
        show_node(root->right);
    }
}

//public :
//    Node *root;

//    Splay_tree(Node *root = nullptr) : root(root) {}
//here past what in the bottom

Node *find(Node *root, int index) {//вызывается только если точно есть индекс в дереве

    return splay(find_easy(root, index));
}

void show(Node *root) {
    show_node(root);
    cout << "\n";
}

//};

Node *merge(Node *x_root, Node *y_root) {
    if (y_root == nullptr)
        return x_root;
    y_root = find(y_root, 1);
    y_root->left = x_root;
    set_parent(x_root, y_root);
    recalc(y_root);
    return y_root;
}

pair<Node *, Node *> split(Node *root, int index) {//{ind < index; ind >= index}
    if (index > root->sum)
        return {root, nullptr};
    if (index <= 0)
        return {nullptr, root};
    root = find(root, index);
    Node *rr = root->right;
    set_parent(rr, nullptr);
    root->right = nullptr;
    recalc(root);
    recalc(rr);
    return {root, rr};
}

Node *add_to_end(Node *tree, int k) {
    return merge(tree, new Node(k));
}

Node *cut_out(Node *node) {
    splay(node);
    pair<Node *, Node *> pair = split(node, get_sum(node->left) + 1);
    if (pair.second != nullptr) {
        find(pair.second, 1)->link = node;
    }
    return pair.first;
}

Node *expose(Node *node) {
    node = find(cut_out(node), 1);
    Node *next;
    while (node->link != nullptr) {
        next = cut_out(node->link);
        node->link = nullptr;
        node = find(merge(next, node), 1);
    }
    return node;
}

Node *link(Node *child, Node *parent) {
    //   parent->childrens.insert(child);
    child->link = parent;
    return expose(child);

}

void cut(Node *child, Node *parent) {
    //  parent->childrens.erase(child);
    expose(parent);
    child->link = nullptr;
}

Node *find_root(Node *node) {
    return expose(node);
}

Node *lca(Node *u, Node *v) {
    expose(u);
    expose(v);
    return find_easy(splay(u), 1)->link;
}

Node * find_alive(Node * node){
    if (node->alive) return node;
    node->alive_acs = find_alive(node->alive_acs);
    return node->alive_acs;
}

int main() {
    vector<Node *> nodes;
    nodes.push_back(new Node(1));
    int m;
    cin >> m;
    char command;
    int parent;
    for (int i = 2; i <= m+1; i++) {
        cin >> command;
        switch (command) {
            case '+': {
                cin >> parent;
                nodes.push_back(new Node(nodes.size() + 1));
                link(nodes[nodes.size()-1], nodes[parent-1]);
               // nodes[parent-1]->childrens.insert(nodes.size());
                nodes[nodes.size()-1]->real_parent = nodes[parent-1];
                break;
            }
            case '-': {
                cin >> parent;
                nodes[parent-1]->alive = false;
                nodes[parent-1]->alive_acs = nodes[parent-1]->real_parent->alive_acs;
                break;
            }
            case '?': {
                int u, v;
                cin >> u >> v;
                if (u == v) {
                    cout << u << "\n";
                    break;
                }
                if (u < v) swap(u, v);
                cout << find_alive(lca(nodes[u - 1], nodes[v - 1]))->inf << "\n";
                break;
            }
        }
    }
}
