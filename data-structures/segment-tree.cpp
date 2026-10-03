#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Node {
    ll val = 0;
};
struct SegTree {
  int n;
  vector<Node> t;
  SegTree(int n) : n(n), t(4*n) {}
  Node merge(const Node& a,const Node& b) {
    Node res;
    return res;
  }
  void update(int i, ll v, int x, int l, int r) {
    if (r - l == 1) {t[x].val = v; return; }
    int m = (l+r)/2;
    if (i < m)update(i,v,2*x+1,l,m);
    else      update(i,v,2*x+2,m,r);
    t[x]=merge(t[2*x+1],t[2*x+2]);
  }
  Node query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) return t[x];
    int m = (l + r) / 2;
    if (qr <= m) return query(ql,qr,2*x+1,l,m);
    if (ql >= m) return query(ql,qr,2*x+2,m,r);
    return merge(query(ql,qr,2*x+1,l,m),
                  query(ql,qr,2*x+2,m,r));
  }
  void update(int i, ll v){ update(i,v, 0,0,n); }
  Node query(int l, int r){ return query(l,r,0,0,n); }
};
