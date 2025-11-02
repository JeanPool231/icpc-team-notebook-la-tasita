#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

struct FenwickTree {
  vector<ll> bit; 
  ll n;

  FenwickTree(ll n) {
    this->n = n;
    bit.assign(n, 0);
  }

  FenwickTree(vector<ll> const &a) : FenwickTree(a.size()) {
    for (size_t i = 0; i < a.size(); i++)
      add(i, a[i]);
  }

  ll sum(ll r) {
    ll ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];
    return ret;
  }

  ll sum(ll l, ll r) {
    return sum(r) - sum(l - 1);
  }

  void add(ll idx, ll delta) {
    for (; idx < n; idx = idx | (idx + 1))
      bit[idx] += delta;
  }
};


void solve() {
  int n; cin >> n;
  vector<ll> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  FenwickTree ft(arr);

  int m;
  cin >> m;
  for (int i = 1; i <= m; i++) {
    int q,l,r;
    cin >> q >> l >> r;
    if (q == 's') {
      cout << ft.sum(l, r) << " ";
    }
    else {
      int delta = r - arr[l];
      arr[l] = r;
      ft.add(l, delta);
    } 
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
