
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

using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

struct Node {
    int inf;
    Node *left;
    Node *right;
    Node *parent;
    int size;
    Node *link;
    bool rev;

//    set<int> childrens;
    explicit Node(int inf) {
        this->inf = inf;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;
        link = nullptr;
        rev = false;
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

void reverse(Node * node){
    if (node!=nullptr) node->rev ^= true;
}

void push(Node *node) {
    if (node != nullptr && node->rev) {
        swap(node->left, node->right);
        node->rev = false;
        reverse(node->left);
        reverse(node->right);
    }
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
    push(cur_node);
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

Node *add_to_end(Node *tree, int k) {
    return merge(tree, new Node(k));
}

void clean_up(Node *node) {
    if (node == nullptr) return;
    clean_up(node->parent);
    push(node);
}

Node *support_root(Node *node) {
    clean_up(node);
    return splay(node);
}

Node *cut_out(Node *node) {
    support_root(node);
    pair<Node *, Node *> pair = split(node, get_size(node->left) + 1);
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

Node *lca_(Node *u, Node *v) {//v higher u
    expose(u);
    expose(v);
    return find(splay(u), 1)->link;
}

Node *lca(int v, int u, vector<Node *> nodes, vector<int> depth) {//v higher u
    if (u == v) return nodes[v];
    if (depth[u] < depth[v]) swap(u, v);
    return lca_(nodes[u], nodes[v]);
}


Node *find_root(Node *node) {
    return expose(node);
}
void revert(Node * node){
    Node * root =  expose(node);
    reverse(support_root(root));
}

void dfs(int vertex, int prev_vertex, vector<unordered_set<int>> &connect,
         vector<int> &depth, vector<Node *> &nodes) {
    int prevDepth = depth[vertex];
    ++prevDepth;
    connect[vertex].erase(prev_vertex);
    Node *parent_node = nodes[vertex];
    for (int son : connect[vertex]) {
        depth[son] = prevDepth;
        Node *cur_node = nodes[son];
        link(cur_node, parent_node);
        dfs(son, vertex, connect, depth, nodes);
    }
}
void add(Node * node1, Node * node2){
    revert(node1);
    link(node1, node2);
}

void rem(Node * u, Node * v){
    revert(v);
    cut(u, v);
}
bool con(Node * u, Node * v){
    if (find_root(u)==find_root(v)) return true;
    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<Node *> nodes;
    int n, m;
    cin >> n >>m;
    for (int i = 0; i <= n; i++){
        nodes.push_back(new Node(i));
    }
    string command;
    for (int i = 0; i < m; i++){
        cin >> command;
        int a, b;
        cin >> a >> b;
        if (command == "link"){
            add(nodes[a], nodes[b]);
        }else if (command=="connected"){
            cout << con(nodes[a], nodes[b])<<"\n";
        } else if (command=="cut"){
            rem(nodes[a], nodes[b]);
        }
    }
    return 0;
}