#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

struct Summary {
	ll gcd;
	ll cnt;
	Summary(Summary left, Summary right){
		gcd = __gcd(left.gcd,right.gcd);
		cnt = (gcd==left.gcd?left.cnt:0) + (gcd==right.gcd?right.cnt:0);
	}
	Summary(ll gcd, ll cnt) : gcd(gcd), cnt(cnt) {}
	Summary() : gcd(0), cnt(0) {} //elemento neutro
};

struct Node {
  Summary value;
  int start, end;
  Node* left;
  Node* right;
  ll lazy;

  Node(int start, int end) : 
    start(start), end(end), value(0,0), lazy(0), left(nullptr), right(nullptr) {}
};

Node* build(vector<ll> &arr, int l, int r){
  Node* node = new Node(l,r);
  if(l == r) {
    node->value = Summary(arr[l],1);
    return node;
  }

  int m = (l + r) / 2;
  node->left = build(arr, l, m);
  node->right = build(arr, m+1, r);
  node->value = Summary(node->left->value, node->right->value);
  return node;
}

Summary query(Node* root, int start, int end) {
  if(start > end) return Summary();
  if(root->start == start && root->end == end)
    return root->value;
  
  int m = (root->start+root->end)/2;
  Summary ans(query(root->left,start,min(m,end)), query(root->right,max(m+1,start),end));
  return ans;
}

void solve() {
  int n; cin >> n;
  vector<ll> arr(n);
  for(int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  Node* root = build(arr, 0, n-1);
  int m; cin >> m;
  while(m--) {
    int l,r;
    cin >> l >> r;
    l--,r--;
    Summary ans = query(root, l, r);
    cout << (r - l + 1) - (ans.cnt)  << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}
