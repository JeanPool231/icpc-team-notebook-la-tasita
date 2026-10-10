struct Fenwick {
  int n;
  vector<ll> t;
  Fenwick(int n) : n(n), t(n+1) {}
  Fenwick(const vector<ll>& a) : n(a.size()), t(n+1) { // O(n)
    for (int i = 1; i <= n; i++) {
      t[i] += a[i-1];
      int j = i + (i&-i);
      if (j <= n) t[j] += t[i];
    }
  }
  void add(int i, ll v) { for (i++; i <= n; i += i&-i) t[i] += v; }
  ll pre(int i) { // sum of [0, i)
    ll s = 0;
    for (; i > 0; i -= i&-i) s += t[i];
    return s;
  }
  ll query(int l, int r) { return pre(r) - pre(l); } // [l, r)
  void set(int i, ll v) { add(i, v - query(i,i+1)); }
  int lower_bound(ll v) { // first i with pre(i+1) >= v, (values >= 0), n if none
    int pos = 0;
    for (int k = 1<<__lg(n); k; k >>= 1)
      if (pos+k <= n && t[pos+k] < v) { pos += k; v -= t[pos]; }
    return pos;
  }
};
