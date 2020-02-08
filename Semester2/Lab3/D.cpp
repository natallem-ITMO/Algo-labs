#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
std::ifstream cin("a.in");
std::ofstream cout("a.out");

struct Node {
    //int key;
    Node *p, *l, *r;


    Node(int key, Node *p = nullptr, Node *l = nullptr, Node *r = nullptr) :
            /*key(key),*/ p(p), l(l), r(r) {}
};

struct SplayTree {
    Node *root;

    SplayTree(Node *root = nullptr) : root(root) {};

    Node *right_rotation(Node *x) {
        if (x == nullptr)
            return nullptr;
        Node *y = x->l;
        Node *A = y->l;
        Node *B = y->r;
        Node *C = x->r;
        y->l = A;
        y->r = x;
        x->l = B;
        x->r = C;
        return y;
    }

    Node *left_rotation(Node *x) {
        if (x == nullptr)
            return nullptr;
        Node *y = x->r;
        Node *A = x->l;
        Node *B = y->l;
        Node *C = y->r;
        y->l = x;
        y->r = C;
        x->l = A;
        x->r = B;
        return y;
    }

    int splay_this(int k) {
        root = splay(root, k);
        return root->key;
    }

    Node *splay(Node *root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key > key) {
            if (root->l == nullptr) return root;

            if (root->l->key > key) {
                root->l->l = splay(root->l->l, key);
                root = right_rotation(root);
            } else if (root->l->key < key) // Zig-Zag (Left Right)
            {
                root->l->r = splay(root->l->r, key);

                if (root->l->r != nullptr)
                    root->l = left_rotation(root->l);
            }

            return (root->l == nullptr) ? root : right_rotation(root);
        } else {
            if (root->r == nullptr) return root;

            if (root->r->key > key) {
                root->r->l = splay(root->r->l, key);
                if (root->r->l != nullptr)
                    root->r = right_rotation(root->r);
            } else if (root->r->key < key)// Zag-Zag (Right Right)
            {
                root->r->r = splay(root->r->r, key);
                root = left_rotation(root);
            }
            return (root->r == nullptr) ? root : left_rotation(root);
        }
    }

    Node *search(int key) {
        return splay(root, key);
    }

    void show_this() {
        show(root);
        cout << "\n";
    }

    void show(Node *root) {
        if (root != nullptr) {
            show(root->l);
            cout << root->key << " ";
            show(root->r);
        }
    }

    void show_root() {
        if (root == nullptr) cout << "-";
        else cout << root->key;
        cout << "\n";
    }

    void insert(int k) {
        if (root == nullptr) {
            root = new Node(k);
        }
        root = splay(root, k);
        if (root->key == k) return;
        Node *new_node = new Node(k);
        if (root->key > k) {
            new_node->r = root;
            new_node->l = root->l;
            root->l = nullptr;
        } else {
            new_node->l = root;
            new_node->r = root->r;
            root->r = nullptr;
        }
        root = new_node;
    }

    pair<Node *, Node *> split(int x) {//{<=x ; >x}
        int res = splay_this(x);
        if (root->key <= x) {
            Node *greater = root->r;
            root->r = nullptr;
            return {root, greater};
        }
        if (root->key > x) {
            Node *smaller = root->l;
            root->l = nullptr;
            return {smaller, root};
        }
    }

    pair<SplayTree *, SplayTree *> split_tree(int x) {//{<=x ; >x}
        pair<Node *, Node *> pair = split(x);
        return {new SplayTree(pair.first), new SplayTree(pair.second)};
    }

    void merge(SplayTree *greater) {
        set_max_root();
        if (root== nullptr){
            root=greater->root;
            return;
        }
        root->r = greater->root;
    }

    Node *splay_max() {
        if (root== nullptr) return root;
        if (root->r == nullptr) return root;
        root->r->r = splay_max();
        root = left_rotation(root);
        return (root->r == nullptr) ? root : left_rotation(root);
    }

    void set_max_root(){
        root = splay_max();
    }
    void remove(int x){
        int res = splay_this(x);
        if (res==x) {
           SplayTree * smaller = new SplayTree(this->root->l);
           smaller->merge(new SplayTree(this->root->r));
           root = smaller->root;
        }
    }


};

void insertTest(SplayTree *tree, int x, int y) {

    for (int i = x; i <= y; i++) {
        tree->insert(i);
    }
}

int main() {

    SplayTree *tree = new SplayTree;


    insertTest(tree, 3, 9);
   tree->remove(4);
   tree->show_this();



    return 0;
}
