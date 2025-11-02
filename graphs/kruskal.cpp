#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

struct Edge {
  ll u, v, weight;
  bool operator<(Edge const& other) const {
    return weight < other.weight;
  }
};

struct DSU {
  vector<int> parent, size;

  DSU(int n) {
    parent.resize(n);
    size.assign(n, 1);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find(parent[v]);
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (size[a] < size[b]) swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
  }
};

ll kruskal(int n, vector<Edge>& edges, vector<Edge>& result) {
  sort(edges.begin(), edges.end());
  DSU dsu(n);
  ll cost = 0;

  for (auto& e : edges) {
    if (dsu.unite(e.u, e.v)) {
      cost += e.weight;
      result.push_back(e);
    }
  }
  return cost;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<Edge> edges;
  edges.reserve(m);

  for (int i = 0; i < m; i++) {
    ll u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    edges.push_back({u, v, w});
  }

  vector<Edge> result;
  ll total_cost = kruskal(n, edges, result);

  if(result.size() == n-1) {
    cout << total_cost << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }

  // Optional: print MST edges
  // for (auto &e : result)
  //     cout << e.u + 1 << " " << e.v + 1 << " " << e.weight << endl;
}

