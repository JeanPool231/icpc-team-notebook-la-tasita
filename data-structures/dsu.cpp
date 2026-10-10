struct DSU {
  int n;
  vector<int> p, siz;
  DSU(int n) : n(n), p(n), siz(n,1) { iota(p.begin(),p.end(),0); }
  int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
  bool unite(int a, int b) { // false if already in the same set
    a = find(a); b = find(b);
    if (a == b) return false;
    if (siz[a] < siz[b]) swap(a,b);
    p[b] = a; siz[a] += siz[b];
    return true;
  }
  bool same(int a, int b) { return find(a) == find(b); }
  int size(int x) { return siz[find(x)]; }
};
