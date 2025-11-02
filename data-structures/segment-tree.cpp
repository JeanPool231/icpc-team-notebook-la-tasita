#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

int n, t[4*MAXN];

void build(vector<int> a, int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {
    int tm = tl + (tr - tl) / 2;
    build(a, v*2, tl, tm);
    build(a, v*2+1, tm+1, tr);
    t[v] = t[v*2] + t[v*2+1];
  }
}

void update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    t[v] = new_val;
  } else {
    int tm = tl + (tr - tl) / 2;
    if (pos <= tm) 
      update(v*2, tl, tm, pos, new_val);
    else
      update(v*2+1, tm+1, tr, pos, new_val);
    t[v] = t[v*2] + t[v*2+1];
  }
}

int sum(int v, int tl, int tr, int l, int r) {
  if (l > r) 
    return 0;
  if (l == tl && r == tr) {
    return t[v];
  }
  int tm = (tl + tr) / 2;
  return sum(v*2, tl, tm, l, min(r, tm))
    + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}


int main(){
  vector<int> arr = {1,1,1,1,1};
  int n = arr.size();
  build(arr, 1, 0, n-1);
  cout << sum(1,0,n-1,0,4) << endl; // 5
  cout << sum(1,0,n-1,0,1) << endl; // 2
  cout << sum(1,0,n-1,1,4) << endl; // 4

  update(1, 0, n-1, 4, 0);

  cout << sum(1,0,n-1,0,4) << endl; // 4
  cout << sum(1,0,n-1,0,1) << endl; // 2
  cout << sum(1,0,n-1,1,4) << endl; // 3
  return 0;
}
