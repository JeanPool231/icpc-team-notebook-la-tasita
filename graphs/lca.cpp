#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;

int n, l;
vector<vector<pair<int,int>>> adj;
int timer;
vector<int> tin, tout;
vector<vector<int>> up;
vector<ll> dist; // distance from root to node

void dfs(int v, int p)
{
  tin[v] = ++timer;
  up[v][0] = p;

  for (int i = 1; i <= l; ++i)
    up[v][i] = up[up[v][i-1]][i-1];

  for (auto [u, w] : adj[v]) {
    if (u != p) {
      dist[u] = dist[v] + w;
      dfs(u, v);
    }
  }

  tout[v] = ++timer;
}

bool is_ancestor(int u, int v) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
  if (is_ancestor(u, v)) return u;
  if (is_ancestor(v, u)) return v;
  for (int i = l; i >= 0; --i)
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  return up[u][0];
}

ll distance(int u, int v)
{
  int ancestor = lca(u, v);
  return dist[u] + dist[v] - 2 * dist[ancestor];
}

void preprocess(int root)
{
  tin.resize(n);
  tout.resize(n);
  dist.assign(n, 0);
  timer = 0;
  l = ceil(log2(n));
  up.assign(n, vector<int>(l + 1));
  dfs(root, root);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  adj.assign(n, {});

  for (int i = 0; i < n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    --u; --v;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  preprocess(0); // root = 0

  int q; cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    cout << distance(u, v) << endl;
  }
}

