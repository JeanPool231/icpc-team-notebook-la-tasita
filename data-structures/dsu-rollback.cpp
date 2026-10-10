struct DSURollback {
  int n, comps;
  vector<int> p, siz;
  vector<pair<int,int>> st; // history: (child root, parent root), (-1,-1) if no merge
  DSURollback(int n) : n(n), comps(n), p(n), siz(n,1) { iota(p.begin(),p.end(),0); }
  int find(int x) { while (p[x] != x) x = p[x]; return x; } // no path compression
  bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) { st.push_back({-1,-1}); return false; }
    if (siz[a] < siz[b]) swap(a,b);
    p[b] = a; siz[a] += siz[b]; comps--;
    st.push_back({b,a});
    return true;
  }
  void rollback() { // undoes the last unite (even if it did not merge)
    auto [b,a] = st.back(); st.pop_back();
    if (b < 0) return;
    p[b] = b; siz[a] -= siz[b]; comps++;
  }
  bool same(int a, int b) { return find(a) == find(b); }
  int size(int x) { return siz[find(x)]; }
};
