#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long
#define endl '\n'

const int INF = 1 << 30;
const int MAXN = 1e5+5;

int n, l;
vector<vector<int>> adj;
vector<int> height;

int timer;
vector<vector<int>> st; // sparse table

void dfs(int u, int p, int h) {
  height[u] = h;
  st[u][0] = p;
  for (int i = 1; i <= l; i++) {
    st[u][i] = st[st[u][i - 1]][i - 1];
  }
  for (int v : adj[u]) {
    if (v != p) {
      dfs(v, u, h + 1);
    }
  }
}

int lca(int u, int v) {
  if(height[u] > height[v]) swap(u,v);

  int diff = height[v] - height[u];

  for(int i = 0; i <= l; i++) {
    if((diff >> i) & 1) {
      v = st[v][i];
    }
  }

  if(u == v) return u;

  for(int i = l; i >= 0; i--) {
    if(st[u][i] != st[v][i]) {
      u = st[u][i];
      v = st[v][i];
    }
  }

  return st[u][0];   
}

void preprocess(int root) {
  l = ceil(log2(n));
  st.assign(n, vector<int>(l + 1));
  height.assign(n,0);
  dfs(root, root, 0);
}

void solve() {
  cin >> n;
  vector<int> parent(n,-1);
  adj.clear();
  adj.resize(n+1);
  for(int u = 0; u < n; u++) {
    int m; cin >> m;
    for(int j = 0; j < m; j++) {
      int v; cin >> v; v--;
      adj[u].push_back(v);
      parent[v] = u;
    }
  }  

  int root = 0;
  for(int i = 0; i < n; i++) {
    if(parent[i] == -1) {
      root = i;
      break;
    }
  }

  preprocess(root);

  int x; cin >> x;
  while(x--) {
    int u,v;
    cin >> u >> v;
    u--;v--;
    cout << lca(u,v)+1 << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  for(int i = 1; i <= t; i++) {
    cout << "Case " << i << ":" << endl;
    solve();
  }
}
