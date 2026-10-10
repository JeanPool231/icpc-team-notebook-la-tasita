struct BinLiftW {
  int n, K;
  vector<vector<pair<int,ll>>> g;
  vector<vector<int>> up;
  vector<vector<ll>> mx; // mx[k][v] = max edge weight on the 2^k jump from v
  vector<int> dep;
  ll merge(ll a, ll b) { return max(a,b); } // your merge here
  const ll ID = LLONG_MIN; // identity of merge
  BinLiftW(int n) : n(n), K(__lg(n)+1), g(n), up(K,vector<int>(n)), mx(K,vector<ll>(n,LLONG_MIN)), dep(n) {}
  void add_edge(int a, int b, ll w) { g[a].push_back({b,w}); g[b].push_back({a,w}); }
  void build(int root = 0) {
    vector<int> s = {root};
    up[0][root] = root;
    while (!s.empty()) {
      int u = s.back(); s.pop_back();
      for (auto [v,w] : g[u]) if (v != up[0][u]) { up[0][v] = u; mx[0][v] = w; dep[v] = dep[u]+1; s.push_back(v); }
    }
    for (int k = 1; k < K; k++)
      for (int v = 0; v < n; v++) {
        int m = up[k-1][v];
        up[k][v] = up[k-1][m];
        mx[k][v] = merge(mx[k-1][v],mx[k-1][m]);
      }
  }
  ll query(int a, int b) { // aggregate over edges of the path a-b
    ll res = ID;
    if (dep[a] < dep[b]) swap(a,b);
    for (int k = 0; k < K; k++)
      if ((dep[a]-dep[b])>>k & 1) { res = merge(res,mx[k][a]); a = up[k][a]; }
    if (a == b) return res;
    for (int k = K-1; k >= 0; k--)
      if (up[k][a] != up[k][b]) {
        res = merge(res,merge(mx[k][a],mx[k][b]));
        a = up[k][a]; b = up[k][b];
      }
    return merge(res,merge(mx[0][a],mx[0][b]));
  }
};
