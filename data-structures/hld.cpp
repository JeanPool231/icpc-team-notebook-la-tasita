struct HLDNode { ll val = 0; };
struct HLDTree {
  int n;
  vector<HLDNode> t;
  vector<ll> lazy;
  HLDTree(int n) : n(n), t(4*n), lazy(4*n) {}
  HLDNode merge(const HLDNode& a, const HLDNode& b) { return {a.val + b.val}; }
  void apply(int x, int l, int r, ll v) { t[x].val += v * (r-l); lazy[x] += v; }
  void push(int x, int l, int r) {
    if (!lazy[x] || r-l == 1) return;
    int m=(l+r)/2; apply(2*x+1,l,m,lazy[x]); apply(2*x+2,m,r,lazy[x]); lazy[x]=0;
  }
  void build(const vector<ll>& a, int x, int l, int r) {
    if (r-l==1) { t[x].val=a[l]; return; }
    int m=(l+r)/2; build(a,2*x+1,l,m); build(a,2*x+2,m,r); t[x]=merge(t[2*x+1],t[2*x+2]);
  }
  void build(const vector<ll>& a) { build(a,0,0,n); }
  void update(int ql,int qr,ll v,int x,int l,int r) {
    if (qr<=l || r<=ql) return;
    if (ql<=l && r<=qr) { apply(x,l,r,v); return; }
    push(x,l,r); int m=(l+r)/2; update(ql,qr,v,2*x+1,l,m); update(ql,qr,v,2*x+2,m,r); t[x]=merge(t[2*x+1],t[2*x+2]);
  }
  void update(int l,int r,ll v) { update(l,r,v,0,0,n); }
  HLDNode query(int ql,int qr,int x,int l,int r) {
    if (ql<=l && r<=qr) return t[x];
    push(x,l,r); int m=(l+r)/2;
    if (qr<=m) return query(ql,qr,2*x+1,l,m);
    if (ql>=m) return query(ql,qr,2*x+2,m,r);
    return merge(query(ql,qr,2*x+1,l,m),query(ql,qr,2*x+2,m,r));
  }
  HLDNode query(int l,int r) { return query(l,r,0,0,n); }
};

struct HLD {
  int n;
  vector<vector<int>> g;
  vector<int> par, dep, siz, heavy, head, pos;
  HLDTree st;
  HLD(int n) : n(n), g(n), par(n,-1), dep(n), siz(n,1), heavy(n,-1), head(n), pos(n), st(n) {}
  void add_edge(int a, int b) { g[a].push_back(b); g[b].push_back(a); }
  void build(const vector<ll>& a, int root = 0) {
    vector<int> ord, s = {root};
    while (!s.empty()) { // preorder, sets parent and depth
      int u = s.back(); s.pop_back(); ord.push_back(u);
      for (int v : g[u]) if (v != par[u]) { par[v] = u; dep[v] = dep[u]+1; s.push_back(v); }
    }
    for (int i = n-1; i > 0; i--) siz[par[ord[i]]] += siz[ord[i]];
    for (int i = n-1; i > 0; i--) {
      int u = ord[i], p = par[u];
      if (heavy[p] < 0 || siz[u] > siz[heavy[p]]) heavy[p] = u;
    }
    int cur = 0; head[root] = root; s = {root};
    while (!s.empty()) { // heavy child is pushed last, so it is visited right after u
      int u = s.back(); s.pop_back(); pos[u] = cur++;
      for (int v : g[u]) if (v != par[u] && v != heavy[u]) { head[v] = v; s.push_back(v); }
      if (heavy[u] >= 0) { head[heavy[u]] = head[u]; s.push_back(heavy[u]); }
    }
    vector<ll> b(n);
    for (int i = 0; i < n; i++) b[pos[i]] = a[i];
    st.build(b);
  }
  void update_path(int a, int b, ll v) { // vertices on the path a-b
    for (; head[a] != head[b]; a = par[head[a]]) {
      if (dep[head[a]] < dep[head[b]]) swap(a,b);
      st.update(pos[head[a]],pos[a]+1,v);
    }
    if (dep[a] > dep[b]) swap(a,b);
    st.update(pos[a],pos[b]+1,v);
  }
  HLDNode query_path(int a, int b) {
    HLDNode res; // identity of merge
    for (; head[a] != head[b]; a = par[head[a]]) {
      if (dep[head[a]] < dep[head[b]]) swap(a,b);
      res = st.merge(res,st.query(pos[head[a]],pos[a]+1));
    }
    if (dep[a] > dep[b]) swap(a,b);
    return st.merge(res,st.query(pos[a],pos[b]+1));
  }
  void update_subtree(int u, ll v) { st.update(pos[u],pos[u]+siz[u],v); }
  HLDNode query_subtree(int u) { return st.query(pos[u],pos[u]+siz[u]); }
  int lca(int a, int b) {
    for (; head[a] != head[b]; a = par[head[a]])
      if (dep[head[a]] < dep[head[b]]) swap(a,b);
    return dep[a] < dep[b] ? a : b;
  }
};

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   int n = 5;
//   HLD h(n);
//   h.add_edge(0,1); h.add_edge(0,2); h.add_edge(1,3); h.add_edge(1,4);
//   h.build({1,2,3,4,5});
//   h.update_path(3,2,10);
//   cout << h.query_path(4,2).val << "\n";
//   cout << h.query_subtree(1).val << "\n";
// }
