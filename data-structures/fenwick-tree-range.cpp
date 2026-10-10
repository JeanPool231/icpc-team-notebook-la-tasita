struct FenwickRange {
  int n;
  vector<ll> b1, b2;
  FenwickRange(int n) : n(n), b1(n+1), b2(n+1) {}
  void add(vector<ll>& b, int i, ll v) { for (i++; i <= n; i += i&-i) b[i] += v; }
  ll sum(vector<ll>& b, int i) { ll s = 0; for (; i > 0; i -= i&-i) s += b[i]; return s; }
  void update(int l, int r, ll v) { // a[l..r-1] += v
    add(b1,l,v); add(b1,r,-v);
    add(b2,l,v*l); add(b2,r,-v*r);
  }
  ll pre(int i) { return sum(b1,i)*i - sum(b2,i); } // sum of [0, i)
  ll query(int l, int r) { return pre(r) - pre(l); } // [l, r)
};
