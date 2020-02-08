/*
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
    long long int inf;

    Node *left;
    Node *right;
    Node *parent;
    int size;
    Node *link;
    Node *real_parent;
    long long int add;

//    set<int> childrens;
    explicit Node(long long int inf) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;
        this->inf = inf;
        link = nullptr;
        real_parent = nullptr;
        add = 0;
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

void add_to_node(Node *node, long long int x) {
    if (node != nullptr) node->add += x;
}

long long int true_value(Node *node) {
    return node->inf + node->add;
}


void push(Node *node) {
    if (node != nullptr && node->add != 0) {
        add_to_node(node->left, node->add);
        add_to_node(node->right, node->add);
        node->inf += node->add;
        node->add = 0;
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
}*/
/*
def find(v, lhs):
if v == None:
return None
push(v)
threshold = size(v.left)
if lhs == threshold:
return splay(v)
if lhs < threshold and v.left != None:
return find(v.left, lhs)
if lhs > threshold and v.right != None:
return find(v.right, lhs - threshold - 1)
return splay(v)*//*



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

void show_node(Node *root) {
    if (root != nullptr) {
        push(root);
        show_node(root->left);
        cout << root->inf << " ";
        show_node(root->right);
    }
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

*/
/*Node *add_to_end(Node *tree, int k) {
    return merge(tree, new Node(k));
}*//*


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

void add_to_tree(Node *nodeX, Node *nodeY, long long int to_add) {//nodeX выше чем nodeY
    nodeY = expose(nodeY);
    nodeY->add += to_add;
    if (nodeX->real_parent != nullptr) {
        nodeX = nodeX->real_parent;
        nodeX = expose(nodeX);
        nodeX->add -= to_add;
    }
}

void add(Node *node, long long int to_add) {
    node = expose(node);
    node->add += to_add;
}

void add_after(Node *node, long long int to_add) {
    if (node->real_parent != nullptr) {
        node = node->real_parent;
        add(node, to_add);
    }
}

long long int get_value_in_tree(Node *node) {
    expose(node);
    return true_value(node);
}

void show_all(vector<Node *> nodes) {
    for (int i = 1; i < nodes.size(); i++) {
        cout << i << ": " << get_value_in_tree(nodes[i]) << endl;
    }
    cout << endl;
}

void add_require(int u, int v, long long int d, vector<Node *> nodes, vector<int> depth) {
    //u high v
    Node *lca_this = lca(u, v, nodes, depth);
    add(nodes[v], d);
    add(nodes[u], d);
    add(lca_this, -d);
    add_after(lca_this, -d);

//    cout << "+ " << u << " " << v << " " << d << endl;
//    show_all(nodes);

}

void add_to_tree_to_root(Node *nodeY, int to_add) {//nodeX выше чем nodeY
    nodeY = expose(nodeY);
    nodeY->add += to_add;
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
        cur_node->real_parent = parent_node;
        dfs(son, vertex, connect, depth, nodes);
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
//    scanf("%ll", n);
    cin >> n;
    vector<unordered_set<int>> connect(n + 1);
    vector<int> depth(n + 1);
    vector<Node *> nodes;
    for (int i = 0; i <= n; i++) {
        nodes.push_back(new Node(0));
    }
    for (int i = 1; i < n; i++) {
        int x, y;

        cin >> x >> y;
        connect[x].insert(y);
        connect[y].insert(x);
    }
    depth[1] = 0;
    dfs(1, -1, connect, depth, nodes);

    int m;
    cin >> m;
    char command;

    for (int i = 0; i < m; i++) {
        cin >> command;
        switch (command) {
            case '+': {
                int u, v;//u high v
                long long int d;
                cin >> u >> v >> d;
                add_require(u, v, d, nodes, depth);
                break;
            }
            case '?': {

                int x;
                cin >> x;
                //  cout << command << " " << x << endl;
                cout << get_value_in_tree(nodes[x]) << endl;
                break;
            }

        }
    }
    return 0;
}*/
