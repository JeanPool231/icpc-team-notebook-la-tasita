#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'

const ll INF = 1e18;

struct Dinic {
  struct Edge {
    int to, rev;
    ll cap;
  };

  int n;
  vector<vector<Edge>> g;
  vector<int> level, it;

  Dinic(int n) : n(n), g(n), level(n), it(n) {}

  void add_edge(int u, int v, ll cap) {
    g[u].push_back({v, (int)g[v].size(), cap});
    g[v].push_back({u, (int)g[u].size() - 1, 0});
  }

  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0; q.push(s);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[u] + 1;
          q.push(e.to);
        }
      }
    }
    return level[t] != -1;
  }

  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    for (int &i = it[u]; i < (int)g[u].size(); i++) {
      Edge &e = g[u][i];
      if (e.cap > 0 && level[e.to] == level[u] + 1) {
        ll ret = dfs(e.to, t, min(f, e.cap));
        if (ret > 0) {
          e.cap -= ret;
          g[e.to][e.rev].cap += ret;
          return ret;
        }
      }
    }
    return 0;
  }

  ll max_flow(int s, int t) {
    ll flow = 0, f;
    while (bfs(s, t)) {
      fill(it.begin(), it.end(), 0);
      while ((f = dfs(s, t, INF)) > 0)
        flow += f;
    }
    return flow;
  }

  // Min-cut edges
  void print_mincut_edges(int s) {
    vector<bool> vis(n, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : g[u]) {
        if (e.cap > 0 && !vis[e.to]) {
          vis[e.to] = true;
          q.push(e.to);
        }
      }
    }
    for (int u = 0; u < n; ++u) {
      if (vis[u]) {
        for (auto &e : g[u]) {
          if (!vis[e.to] && e.cap == 0) {
            cout << u + 1 << " " << e.to + 1 << endl;
          }
        }
      }
    }
  }
};

int main() {
  int n,m;
  cin >> n >> m;
  Dinic g(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v;
    w = 1;
    u--;v--;
    g.add_edge(u, v, w);
  }
  cout << g.max_flow(0,n-1) << endl;
  g.print_mincut_edges(0);
}

