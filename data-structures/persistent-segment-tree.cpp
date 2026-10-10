struct Node {
    ll val = 0;
    int lc = 0, rc = 0; // children, 0 = null node
};
struct PerSegTree {
  int n;
  vector<Node> t;
  vector<int> root; // root[i] = root node of version i
  PerSegTree(int n, int cap = 0) : n(n), t(1), root(1,0) { t.reserve(cap+1); }
  Node merge(const Node& a,const Node& b) {
    Node res;
    res.val = a.val + b.val; // your merge here
    return res;
  }
  int build(const vector<ll>& a, int l, int r) {
    int x = t.size(); t.emplace_back();
    if (r - l == 1) {t[x].val = a[l]; return x; }
    int m = (l+r)/2;
    int lc = build(a,l,m), rc = build(a,m,r);
    t[x] = merge(t[lc],t[rc]); t[x].lc = lc; t[x].rc = rc;
    return x;
  }
  int update(int p, int i, ll v, int l, int r) { // returns the new node
    int x = t.size(); t.push_back(t[p]);
    if (r - l == 1) {t[x].val += v; return x; } // your apply here (= v to assign)
    int m = (l+r)/2;
    if (i < m) {int c = update(t[p].lc,i,v,l,m); t[x].lc = c; }
    else       {int c = update(t[p].rc,i,v,m,r); t[x].rc = c; }
    int lc = t[x].lc, rc = t[x].rc;
    t[x] = merge(t[lc],t[rc]); t[x].lc = lc; t[x].rc = rc;
    return x;
  }
  Node query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) return t[x];
    int m = (l + r) / 2;
    if (qr <= m) return query(ql,qr,t[x].lc,l,m);
    if (ql >= m) return query(ql,qr,t[x].rc,m,r);
    return merge(query(ql,qr,t[x].lc,l,m),
                  query(ql,qr,t[x].rc,m,r));
  }
  int kth(int a, int b, ll k) { // k-th smallest (0 idx) in the count difference of roots b and a
    int l = 0, r = n;
    while (r - l > 1) {
      int m = (l+r)/2;
      ll c = t[t[b].lc].val - t[t[a].lc].val;
      if (k < c) {a = t[a].lc; b = t[b].lc; r = m; }
      else       {k -= c; a = t[a].rc; b = t[b].rc; l = m; }
    }
    return l;
  }
  void build(const vector<ll>& a){ root[0] = build(a,0,n); }
  int update(int ver, int i, ll v){ root.push_back(update(root[ver],i,v,0,n)); return root.size()-1; } // new version id
  Node query(int ver, int l, int r){ return query(l,r,root[ver],0,n); }
};

// Ejemplo de uso (main comentado para compilar con la plantilla):
// int main() {
//   vector<ll> values = {2, 1, 3, 4};
//   PerSegTree pst(values.size());
//   pst.build(values);                 // version 0
//   int version1 = pst.update(0, 1, 5); // new version, index 1 += 5
//   cout << pst.query(0, 0, 4).val << "\n";
//   cout << pst.query(version1, 0, 4).val << "\n";
// }
