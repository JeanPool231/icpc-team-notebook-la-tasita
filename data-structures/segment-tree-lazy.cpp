#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Node {
    ll val = 0;
};
struct SegTree {
  int n;
  vector<Node> t;
  vector<ll> lz;
  SegTree(int n) : n(n), t(4*n), lz(4*n) {}
  Node merge(const Node& a,const Node& b) {
    Node res;
    res.val = a.val + b.val;
    return res;
  }
  void apply(int x, int l, int r, ll v) {
    t[x].val += v*(r-l);
    lz[x] += v;
  }
  void push(int x, int l, int r) {
    if (!lz[x]) return;
    int m = (l+r)/2;
    apply(2*x+1,l,m,lz[x]);
    apply(2*x+2,m,r,lz[x]);
    lz[x] = 0;
  }
  void build(const vector<ll>& a, int x, int l, int r) {
    if (r - l == 1) {t[x].val = a[l]; return; }
    int m = (l+r)/2;
    build(a,2*x+1,l,m);
    build(a,2*x+2,m,r);
    t[x]=merge(t[2*x+1],t[2*x+2]);
  }
  void update(int ql, int qr, ll v, int x, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {apply(x,l,r,v); return; }
    push(x,l,r);
    int m = (l+r)/2;
    update(ql,qr,v,2*x+1,l,m);
    update(ql,qr,v,2*x+2,m,r);
    t[x]=merge(t[2*x+1],t[2*x+2]);
  }
  Node query(int ql, int qr, int x, int l, int r) {
    if (ql <= l && r <= qr) return t[x];
    push(x,l,r);
    int m = (l + r) / 2;
    if (qr <= m) return query(ql,qr,2*x+1,l,m);
    if (ql >= m) return query(ql,qr,2*x+2,m,r);
    return merge(query(ql,qr,2*x+1,l,m),
                  query(ql,qr,2*x+2,m,r));
  }
  void build(const vector<ll>& a){ build(a,0,0,n); }
  void update(int l, int r, ll v){ update(l,r,v,0,0,n); }
  Node query(int l, int r){ return query(l,r,0,0,n); }
};
