struct Fenwick2D {
  int n, m;
  vector<vector<ll>> t;
  Fenwick2D(int n, int m) : n(n), m(m), t(n+1,vector<ll>(m+1)) {}
  Fenwick2D(const vector<vector<ll>>& a) : Fenwick2D(a.size(),a[0].size()) {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) add(i,j,a[i][j]);
  }
  void add(int x, int y, ll v) {
    for (int i = x+1; i <= n; i += i&-i)
      for (int j = y+1; j <= m; j += j&-j) t[i][j] += v;
  }
  ll pre(int x, int y) { // sum of [0, x) x [0, y)
    ll s = 0;
    for (int i = x; i > 0; i -= i&-i)
      for (int j = y; j > 0; j -= j&-j) s += t[i][j];
    return s;
  }
  ll query(int x1, int y1, int x2, int y2) { // [x1, x2) x [y1, y2)
    return pre(x2,y2) - pre(x1,y2) - pre(x2,y1) + pre(x1,y1);
  }
  void set(int x, int y, ll v) { add(x,y,v - query(x,y,x+1,y+1)); }
};
