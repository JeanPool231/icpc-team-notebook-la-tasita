struct Fenwick2DRange {
  int n, m;
  vector<vector<ll>> b[4];
  Fenwick2DRange(int n, int m) : n(n), m(m) {
    for (auto& b : b) b.assign(n+1,vector<ll>(m+1));
  }
  void add(int x, int y, ll v) { // point update on the difference array
    ll c[4] = {v, v*x, v*y, v*x*y};
    for (int i = x+1; i <= n; i += i&-i)
      for (int j = y+1; j <= m; j += j&-j)
        for (int k = 0; k < 4; k++) b[k][i][j] += c[k];
  }
  void update(int x1, int y1, int x2, int y2, ll v) { // [x1, x2) x [y1, y2) += v
    add(x1,y1,v); add(x1,y2,-v); add(x2,y1,-v); add(x2,y2,v);
  }
  ll pre(int x, int y) { // sum of [0, x) x [0, y)
    ll s[4] = {};
    for (int i = x; i > 0; i -= i&-i)
      for (int j = y; j > 0; j -= j&-j)
        for (int k = 0; k < 4; k++) s[k] += b[k][i][j];
    return s[0]*x*y - s[1]*y - s[2]*x + s[3];
  }
  ll query(int x1, int y1, int x2, int y2) { // [x1, x2) x [y1, y2)
    return pre(x2,y2) - pre(x1,y2) - pre(x2,y1) + pre(x1,y1);
  }
};
