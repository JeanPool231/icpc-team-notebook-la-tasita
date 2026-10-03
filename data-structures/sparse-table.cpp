#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct SparseTable {
  int n;
  vector<vector<ll>> t;
  ll merge(ll a, ll b) {
    return min(a,b);
  }
  SparseTable(const vector<ll>& a) : n(a.size()) {
    int K = __lg(n) + 1;
    t.assign(K, vector<ll>(n));
    t[0] = a;
    for (int k=1; k<K; k++)
      for (int i = 0; i+(1<<k) <= n; i++)
        t[k][i] = merge(t[k-1][i], t[k-1][i+(1<<(k-1))]);
  }
  ll query(int l, int r) { // [l, r), ops (min, max, gcd, and, or)
    int k = __lg(r-l);
    return merge(t[k][l], t[k][r-(1<<k)]);
  }
  ll query_log(int l, int r) { // [l, r), any associative op
    ll res = 1e18; // identity (0 for sum/xor)
    for (int k = __lg(r-l); k >= 0; k--)
      if (l + (1<<k) <= r) { res = merge(res, t[k][l]); l += 1<<k; }
    return res;
  }
};
