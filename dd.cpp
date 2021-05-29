#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct node {
    int x, y;
    node *right, *left;
    int size;
    node(int _x) {
        x = _x;
        size = 1;
        y = (rand() << 15) + rand();
        left = right = nullptr;
    }
    ~node() {
        if (left) delete left;
        if (right) delete right;
    }
};

int sizeOf (node* root) {
    if (!root) return 0;
    return root->size;
}

void recalc(node *root) {
    if (!root) return;
    root->size = sizeOf(root->left) + sizeOf(root->right) + 1;
}

node* merge(node* l, node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
        l->right = merge(l->right, r);
        recalc(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        recalc(r);
        return r;
    }
}

pair<node*, node*> split(node* root, int val) {
    if (!root) return {nullptr, nullptr};
    if (root->x <= val) {
        pair<node*, node*> ro = split(root->right, val);
        root->right = ro.first;
        recalc(root);
        return {root, ro.second};
    } else {
        pair<node*, node*> ro = split(root->left, val);
        root->left = ro.second;
        recalc(root);
        return {ro.first, root};
    }
}

bool find(node* root, int val) {
    if (!root) return false;
    if (root->x == val)
        return true;
    else if (root->x > val)
        return find(root->left, val);
    else
        return find(root->right, val);
}

node* insert(node* root, int val) {
    if (find(root, val)) return root;
    node* a = new node(val);
    pair<node*, node*> ro = split(root, val);
    return merge(merge(ro.first, a), ro.second);
}

node* erase(node* root, int val) {
    if (!find(root, val)) return root;
    pair<node*, node*> ro1 = split(root, val);
    pair<node*, node*> ro2 = split(ro1.first, val - 1);
    if (ro2.second) delete ro2.second;
    return merge(ro2.first, ro1.second);
}


int main() {

}
