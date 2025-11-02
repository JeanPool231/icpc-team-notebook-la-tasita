#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long
#define endl '\n'

const int INF = 1 << 30;
const int MAXN = 1e5+5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

struct node {
  int key;
  int priority;
  node* left;
  node* right;
  int cnt;
  node(int v) : key(v) {
    priority = random(0,1e9);
    left = right = nullptr; 
    cnt = 1;
  }
};

int cnt(node* t) {
  return t ? t->cnt : 0;
}

void update(node *t) {
  if (t) t->cnt = 1 + cnt(t->left) + cnt(t->right);
}

node* merge(node* a, node* b) {
  if(a == nullptr) return b;
  if(b == nullptr) return a;
  if(a->priority > b->priority) {
    a->right = merge(a->right, b);
    update(a);
    return a;
  } else {
    b->left = merge(a, b->left);
    update(b);
    return b;
  }
}

pair<node*, node*> split(node *T, int k) {
  if(T == nullptr) return {nullptr,nullptr};
  if(T->key <= k) {
    auto p = split(T->right,k); 
    T->right = p.fst;
    update(T);
    return {T, p.snd};
  } else {
    auto p = split(T->left, k);
    T->left = p.snd;
    update(T);
    return {p.fst, T};
  }
}

node* insert(node* T, int x) {
  auto p = split(T,x);
  T = merge(p.fst, new node(x));
  T = merge(T, p.snd);
  return T;
}

node* remove(node* T, int x) {
  auto p = split(T, x);        // p.fst: ≤ x, p.snd: > x
  auto p2 = split(p.fst, x-1); // p2.fst: < x, p2.snd: == x

  // p2.snd contains the node(s) with key = x → we discard it
  return merge(p2.fst, p.snd);
}

bool find(node* T, int x) {
  if (!T) return false;
  if (T->key == x) return true;
  if (x < T->key) return find(T->left, x);
  return find(T->right, x);
}

node* kth(node* t, int k) {
  int left_size = cnt(t->left);
  if (k < left_size) return kth(t->left, k);
  else if (k == left_size) return t;
  else return kth(t->right, k - left_size - 1);
}

void inorder(node* T) {
  if (!T) return;
  inorder(T->left);
  cout << T->key << " ";
  inorder(T->right);
}

void solve() {
  node* root = nullptr;

  root = insert(root, 5);
  root = insert(root, 2);
  root = insert(root, 8);
  root = insert(root, 1);
  root = insert(root, 10);

  cout << "Treap inorder (sorted): ";
  inorder(root); // 1 2 5 8 10
  cout << endl;

  cout << "Find 8? " << (find(root, 8) ? "Yes" : "No") << endl;
  cout << "Find 7? " << (find(root, 7) ? "Yes" : "No") << endl;

  root = remove(root, 5);
  cout << "After removing 5: ";
  inorder(root); // 1 2 8 10
  cout << endl;
}


int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}

