#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

struct Node {
  ll value;
  int start, end;
  Node* left;
  Node* right;
  ll lazy;

  Node(int start, int end) : 
    start(start), end(end), value(0), lazy(0), left(nullptr), right(nullptr) {}
};

ll aggregate_function(ll left, ll right){
  return left + right;
}

Node* build(vector<ll> &arr, int l, int r){
  Node* node = new Node(l,r);
  if(l == r) {
    node->value = arr[l];
    return node;
  }

  int m = (l + r) / 2;
  node->left = build(arr, l, m);
  node->right = build(arr, m+1, r);
  node->value = aggregate_function(node->left->value, node->right->value);
  return node;
}

void pushDown(Node* node) {
  if(node->lazy != 0) {
    if(node->left) {
      int leftRange = node->left->end - node->left->start + 1;
      node->left->value += node->lazy * leftRange;
      node->left->lazy += node->lazy;
    }
    if(node->right) {
      int rightRange = node->right->end - node->right->start + 1;
      node->right->value += node->lazy * rightRange;
      node->right->lazy += node->lazy;
    }
    node->lazy = 0;
  }
}

ll query(Node* root, int start, int end) {
  if(start > end) return 0;
  if(root->start == start && root->end == end)
    return root->value;
  
  pushDown(root);
  int m = (root->start+root->end)/2;
  ll ans = aggregate_function(query(root->left,start,min(m,end)), query(root->right,max(m+1,start),end));
  return ans;
}

Node* persistent_update(Node* root, int pos, ll value) {
  Node* node = new Node(root->start, root->end);
  if(root->start == root->end) {
    node->value = value;
    return node;
  }
  int m = (root->start + root->end) / 2;
  if(pos <= m) {
    node->left = persistent_update(root->left, pos, value);
    node->right = root->right;
  } else {
    node->right = persistent_update(root->right, pos, value);
    node->left = root->left;
  }
  node->value = aggregate_function(node->left->value, node->right->value);
  return node;
}

void update(Node* root, int pos, ll value) {
  if(root->start == root->end) {
    root->value = value;
    return;
  }
  int m = (root->start + root->end) / 2;
  if(pos <= m) {
    update(root->left, pos, value);
  } else {
    update(root->right, pos, value);
  }
  root->value = aggregate_function(root->left->value, root->right->value);
}

void update_range(Node* node, int l, int r, ll delta) {
  if(l > r) return;
  if(l <= node->start && node->end <= r) {
    int rangeLength = node->end - node->start + 1;
    node->value += delta * rangeLength;
    node->lazy += delta;
    return;
  }
  pushDown(node);
  int m = (node->start + node->end) / 2;
  if(l <= m)
    update_range(node->left, l, min(r, m), delta);
  if(r > m)
    update_range(node->right, max(l, m+1), r, delta);
  node->value = aggregate_function(node->left->value, node->right->value);
}

void solve() {
  vector<ll> arr = {1,1,1,1,1,1};
  int n = arr.size();
  Node* root = build(arr,0,n-1);
  cout << query(root,0,n-1) << endl;
  Node* mod1 = persistent_update(root,0,2);
  cout << query(mod1,0,n-1) << endl;
  Node* mod2 = persistent_update(mod1,0,10);
  cout << query(mod2,0,n-1) << endl;

  cout << endl;
  update_range(root, 0, 2, 1);
  cout << query(root,0,n-1) << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}
