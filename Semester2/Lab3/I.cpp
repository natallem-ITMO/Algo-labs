
//#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");
struct Node;
vector<unordered_set<int>> edges(100000 + 1);
vector<unordered_map<int, Node *>> link(100000 + 1);

struct Node {
    string e;

    Node *left;
    Node *right;
    Node *parent;
    int size;

    explicit Node(int s, int t) {
        e = to_string(s) + ":" + to_string(t);

        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;

    }

    ~Node() {
        delete left;
        delete right;
    }
};

int get_size(Node *x) {
    if (x == nullptr) return 0;
    else return x->size;
}

void recalc(Node *node) {
    if (node != nullptr)
        node->size = get_size(node->left) + get_size(node->right) + 1;
}

void set_parent(Node *son, Node *parent) {
    if (son == nullptr) return;
    son->parent = parent;
}

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

Node *find(Node *cur_node, int ind) {
    if (cur_node == nullptr)
        return nullptr;
    // push(cur_node);
    int size_left = get_size(cur_node->left);
    if (size_left + 1 == ind) {
        return splay(cur_node);
    } else if (size_left >= ind) {
        return find(cur_node->left, ind);
    } else {
        return find(cur_node->right, ind - size_left - 1);
    }
}

Node *merge(Node *x_root, Node *y_root) {
    if (x_root == nullptr && y_root == nullptr) return nullptr;
    if (y_root == nullptr)
        return x_root;
    y_root = find(y_root, 1);
    y_root->left = x_root;
    set_parent(x_root, y_root);
    recalc(y_root);
    return y_root;
}


pair<Node *, Node *> split(Node *root, int index) {//{ind < index; ind >= index}
    if (root == nullptr) return {nullptr, nullptr};
    if (index > root->size)
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

pair<Node *, Node *> split_root_in_right(Node *root) {
    Node *ll = root->left;
    set_parent(ll, nullptr);
    root->left = nullptr;
    recalc(root);
    recalc(ll);
    return {ll, root};
}

int index(Node *node) {
    splay(node);
    return get_size(node->left) + 1;
}

pair<Node *, Node *> split_root_in_left(Node *root) {
    Node *rr = root->right;
    set_parent(rr, nullptr);
    root->right = nullptr;
    recalc(root);
    recalc(rr);
    return {root, rr};
}


void add(int u, int v) {
    if (link[u][v] == nullptr && link[v][u] == nullptr) {
        link[u][v] = new Node(u, v);
        link[v][u] = new Node(v, u);
    }
    if (edges[u].empty() && edges[v].empty()) {
        Node *root = merge(link[u][v], link[v][u]);
    } else if (edges[u].empty() || edges[v].empty()) {
        if (edges[u].empty()) swap(u, v);
        int edge = *edges[u].begin();
        Node *cur_node = link[u][edge];
        cur_node = splay(cur_node);
        pair<Node *, Node *> sp = split_root_in_right(cur_node);
        Node *root;
        root = merge(link[u][v], link[v][u]);
        root = merge(sp.first, root);
        root = merge(root, sp.second);
    } else {
        int end_edge_u = *edges[u].begin();
        int end_edge_v = *edges[v].begin();
        Node *node_to_split_u = link[u][end_edge_u];
        Node *node_to_split_v = link[v][end_edge_v];
        pair<Node *, Node *> sp_u = split_root_in_right(splay(node_to_split_u));
        pair<Node *, Node *> sp_v = split_root_in_right(splay(node_to_split_v));
        Node *root = merge(sp_u.first, link[u][v]);
        root = merge(root, sp_v.second);
        root = merge(root, sp_v.first);
        root = merge(root, link[v][u]);
        root = merge(root, sp_u.second);
    }
    edges[u].insert(v);
    edges[v].insert(u);
}

void cut(int u, int v) {
    if (edges[u].size() == 1 && edges[v].size() == 1) {
        split_root_in_right(splay(link[u][v]));
        split_root_in_left(splay(link[u][v]));
    } else {
        if (edges[u].size() == 1) swap(u, v);
        Node *n1 = link[u][v];
        Node *n2 = link[v][u];
        int index_n1 = index(n1);
        int index_n2 = index(n2);
        if (index_n1 > index_n2) swap(n1, n2);
        pair<Node *, Node *> A = split_root_in_right(splay(n1));
        pair<Node *, Node *> n1_ = split_root_in_left(n1);
        pair<Node *, Node *> B = split_root_in_right(splay(n2));
        pair<Node *, Node *> C_ = split_root_in_left(n2);
        Node *root = merge(A.first, C_.second);
    }
    edges[u].erase(v);
    edges[v].erase(u);
}

int size(int v) {
    if (edges[v].empty()) return 1;
    Node *vv = link[v][*edges[v].begin()];
    int size = splay(vv)->size;
    return (size / 2) + 1;
}

Node *root(Node *node) {
    while (node->parent != nullptr) {
        node = node->parent;
    }
    return node;
}

bool connect(int v, int u) {
    if (edges[v].empty() || edges[u].empty())
        return false;
    Node *edge_v = link[v][*edges[v].begin()];
    Node *edge_u = link[u][*edges[u].begin()];
    if (root(edge_u) == root(edge_v)) return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    string command;
    for (int i = 0; i < m; i++) {
        cin >> command;
        int a, b;
        if (command == "link") {
            cin >> a >> b;
            add(a, b);
        } else if (command == "cut") {
            cin >> a >> b;
            cut(a, b);
        } else if (command == "size") {
            cin >> a;
            cout << size(a) << "\n";
        } else if (command == "connected") {
            cin >> a >> b;
            cout << connect(a,b) << "\n";
        }
    }

    return 0;
}