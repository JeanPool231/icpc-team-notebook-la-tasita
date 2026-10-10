struct BinLift {
  int n, K;
  vector<vector<int>> g, up;
  vector<int> dep;
  BinLift(int n) : n(n), K(__lg(n)+1), g(n), up(K,vector<int>(n)), dep(n) {}
  void add_edge(int a, int b) { g[a].push_back(b); g[b].push_back(a); }
  void build(int root = 0) {
    vector<int> s = {root};
    up[0][root] = root; // root is its own parent
    while (!s.empty()) { // iterative dfs
      int u = s.back(); s.pop_back();
      for (int v : g[u]) if (v != up[0][u]) { up[0][v] = u; dep[v] = dep[u]+1; s.push_back(v); }
    }
    for (int k = 1; k < K; k++)
      for (int v = 0; v < n; v++) up[k][v] = up[k-1][up[k-1][v]];
  }
  int kth(int u, int k) { // k-th ancestor of u, root if k > dep[u]
    for (int i = 0; i < K; i++) if (k>>i & 1) u = up[i][u];
    return u;
  }
  int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a,b);
    a = kth(a,dep[a]-dep[b]);
    if (a == b) return a;
    for (int k = K-1; k >= 0; k--)
      if (up[k][a] != up[k][b]) { a = up[k][a]; b = up[k][b]; }
    return up[0][a];
  }
  int dist(int a, int b) { return dep[a]+dep[b]-2*dep[lca(a,b)]; }
};
