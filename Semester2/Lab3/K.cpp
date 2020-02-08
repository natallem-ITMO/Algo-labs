/*
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
/*
#define _CRT_SECURE_NO_WARNINGS
*/
//#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <deque>
#include <cmath>
#include <map>
#include <string>
#include <set>
#include <queue>
#include <iomanip>
#include <bitset>
#include <cassert>
#include <random>
/*
typedef long double ld;
typedef long long int64_t ll;
typedef ulong long int64_t ull;
typedef long long int32_t long long int32;
*/
using namespace std;
//std::ifstream cin("a.in");
//std::ofstream cout("a.out");

// uncomment this for more memory. Number is memory - byte
//#pragma comment (linker, "/STACK:5000000000")

//////////////////////////////////////////////////////////////////
// SYSTEM STARTS

//////////////////////////////////////////////////////////////////
// UTILS
struct Node;
vector<long long int> level;
vector<long long int> parent;
vector<vector<long long int>> edges;
long long int n;
vector<Node *> nodes;
long long int cur_father;
long long int cur_distance;
long long int cur_amount;
long long int cur_distance_subtree;
long long int cur_index_subtree;

struct Node {
    long long int key;
    bool color;
    long long int blacks;
    long long int whites;
    long long int add_black;
    long long int add_white;
    long long int path_black;
    long long int path_white;
    vector<pair<long long int, long long int>> centroids;


    Node(long long int key) {
        this->key = key;
        color = false;
        blacks = 1;
        whites = 0;
        add_black = 0;
        add_white = 0;
        path_black = 0;
        path_white = 0;
    };
};

long long int center_size(long long int v, long long int size, long long int &center, long long int p = -1) {
    long long int sum = 1;
    for (long long int x : edges[v])
        if (level[x] == -1 && x != p) {
            sum += center_size(x, size, center, v);
        }
    if (center == -1 && (2 * sum >= size || p == -1))
        center = v;
    return sum;
}

void decompose(long long int v, long long int size, long long int depth, long long int last, vector<Node *> &nodes) {
    vector<long long int> *level_ = &level;
    vector<long long int> *parent_ = &parent;
    vector<vector<long long int>> *graph_ = &edges;
    long long int *n_ = &n;
    long long int center = -1;
    center_size(v, size, center);
    level[center] = depth;
    parent[center] = last;
    // centroids.push_back(last);
    nodes[center]->centroids = nodes[last]->centroids;
    nodes[center]->centroids.push_back({last, 0});
    for (long long int x : edges[center]) {
        if (level[x] == -1)
            decompose(x, size / 2, depth + 1, center, nodes);
    }
}

void sh_v(vector<pair<long long int, long long int>> &f) {
    for (long long int i = 1; i < f.size(); i++){
        cout << f[i].first << "-" << f[i].second << " ";
    }
    cout << endl;
}

long long int is_father_centroid(long long int node, long long int father) {
    for (long long int i = 0; i < nodes[node]->centroids.size(); i++) {
        if (nodes[node]->centroids[i].first == father) return i;
    }
    return -1;

}

void set_distance(long long int dis, long long int cur_vertex, long long int prev) {
    vector<Node *> &nodess = nodes;
    long long int &cur_index_subtrees = cur_index_subtree;
    long long int &cur_fathers = cur_father;
    long long int index = is_father_centroid(cur_vertex, cur_father);
    if (index != -1 || dis == 0) {
        if (nodes[cur_vertex]->centroids.size() == nodes[cur_father]->centroids.size() + 1)
            cur_index_subtree = cur_vertex;
        if (index != -1) nodes[cur_vertex]->centroids[index].second = dis;
        cur_distance += dis;
        cur_distance_subtree += dis;
        cur_amount++;
        for (long long int x : edges[cur_vertex]) {
            if (x != prev) {
                if (dis == 0) {
                    cur_distance_subtree = 0;
                    cur_index_subtree = -1;
                }
                set_distance(dis + 1, x, cur_vertex);
                if (dis == 0) {
                    if (cur_index_subtree != -1) nodes[cur_index_subtree]->add_black = cur_distance_subtree;
                }
            }
        }
    }
}

void make_black(Node *node) {
    node->blacks++;
    node->whites--;
    node->color = false;
    node->add_white -= node->centroids[node->centroids.size()-1].second;
    node->add_black += node->centroids[node->centroids.size()-1].second;
    for (long long int i = node->centroids.size() - 1; i > 1; i--) {
        Node *father_centroid = nodes[node->centroids[i].first];
        father_centroid->blacks++;
        father_centroid->whites--;
        father_centroid->path_black += node->centroids[i].second;
        father_centroid->path_white -= node->centroids[i].second;
        father_centroid->add_black += node->centroids[i - 1].second;
        father_centroid->add_white -= node->centroids[i - 1].second;
    }
    if (node->centroids.size() > 1) {
        Node *father_centroid = nodes[node->centroids[1].first];
        father_centroid->blacks++;
        father_centroid->whites--;
        father_centroid->path_black += node->centroids[1].second;
        father_centroid->path_white -= node->centroids[1].second;
    }

}

void make_white(Node *node) {
    node->blacks--;
    node->whites++;
    node->color = true;
    node->add_white += node->centroids[node->centroids.size()-1].second;
    node->add_black -= node->centroids[node->centroids.size()-1].second;
    for (long long int i = node->centroids.size() - 1; i > 1; i--) {

        Node *father_centroid = nodes[node->centroids[i].first];
        father_centroid->blacks--;
        father_centroid->whites++;
        father_centroid->path_black -= node->centroids[i].second;
        father_centroid->path_white += node->centroids[i].second;
        father_centroid->add_black -= node->centroids[i - 1].second;
        father_centroid->add_white += node->centroids[i - 1].second;
    }
    if (node->centroids.size() > 1) {
        Node *father_centroid = nodes[node->centroids[1].first];
        father_centroid->blacks--;
        father_centroid->whites++;
        father_centroid->path_black -= node->centroids[1].second;
        father_centroid->path_white += node->centroids[1].second;
    }
}

void change_color(long long int vertex) {
    Node *node = nodes[vertex];
    if (node->color) make_black(node);
    else make_white(node);
}

long long int req_w(long long int vertex) {
    Node *node = nodes[vertex];
    long long int ans = 0;
    ans = node->path_white;
    long long int subtract = node->add_white;
    long long int sub_vertix = node->whites;
    for (long long int i = node->centroids.size() - 1; i >= 1; i--) {
        Node *father_centroid = nodes[node->centroids[i].first];
        ans = ans + (father_centroid->path_white - subtract) +
              ((node->centroids[i].second) * (father_centroid->whites- sub_vertix));
        subtract = father_centroid->add_white;
        sub_vertix = father_centroid->whites;
    }
    return ans;
}

long long int req_b(long long int vertex) {
    Node *node = nodes[vertex];
    long long int ans = 0;
    ans = node->path_black;
    long long int subtract = node->add_black;
    long long int sub_vertix = node->blacks;
    for (long long int i = node->centroids.size() - 1; i >= 1; i--) {
        Node *father_centroid = nodes[node->centroids[i].first];
        long long int x = father_centroid->path_black - subtract;
        long long int y = (node->centroids[i].second) * (father_centroid->blacks - sub_vertix);
        ans += (father_centroid->path_black - subtract) + ((node->centroids[i].second) * (father_centroid->blacks - sub_vertix));
        subtract = father_centroid->add_black;
        sub_vertix = father_centroid->blacks;
    }
    return ans;
}

long long int query(long long int vertex) {
    if (nodes[vertex]->color) return req_w(vertex);
    return req_b(vertex);
}
void show_nodes(){
    for (long long int i = 0; i < nodes.size(); i++) {
        cout << i << " - ";

        cout <<"bl="<<nodes[i]->blacks  <<" wt="<<nodes[i]->whites <<" p_b="<<nodes[i]->path_black <<" p_w="<<nodes[i]->path_white
        <<" a_b="<<nodes[i]->add_black<<" a_w="<<nodes[i]->add_white<<endl;
        sh_v(nodes[i]->centroids);
    }
}

int main() {
    long long int m;
    cin >> n >> m;
    vector<long long int> s;
    vector<Node *> &nodess = nodes;
    bool debug = 0;


    for (long long int i = 0; i <= n; i++) {
        level.push_back(-1);
        parent.push_back(0);
        edges.push_back(s);
        nodes.push_back(new Node(i));
    }
    for (long long int i = 1; i < n; i++) {
        long long int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    decompose(1, n, 0, 0, nodes);

    for (long long int i = 1; i < nodes.size(); i++) {
        cur_distance = 0;
        cur_amount = 0;
        cur_father = i;
        set_distance(0, i, -1);

        nodes[i]->path_black = cur_distance;
        nodes[i]->blacks = cur_amount;
        int x = 10;
    }

    for (long long int i = 0; i < m; i++) {
        long long int a, b;
        cin >> a >> b;
        if (a == 1) {
            change_color(b);
        } else {
            cout << query(b)<<"\n";

        }
    }
    return 0;
}
