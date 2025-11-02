#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const ll INF = LONG_LONG_MAX;
const int MAXN = 1e5+5;

struct Edge {
  int u, v;
  ll weight;
};

int n,m;
vector<Edge> edges;

// Bellman-Ford algorithm to detect negative cycles and find shortest paths
bool bellman(int src, vector<ll> &dist) {
  dist.assign(n + 1, INF);
  dist[src] = 0; 
  for(int i = 2; i <= n; i++) 
  { 
    for (int j = 0; j < m; j++) 
    { 
      int u = edges[j].u; 
      int v = edges[j].v; 
      ll weight = edges[j].weight;
      if (dist[u]!=INF && dist[u] + weight < dist[v]) 
        dist[v] = dist[u] + weight;
    } 
  }
  for (int i = 0; i < m; i++) 
  { 
    int u = edges[i].u; 
    int v = edges[i].v; 
    ll weight = edges[i].weight;
    // True if neg-cylce exists
    if (dist[u]!=INF && dist[u] + weight < dist[v]) 
      return true;
  }
  return false;
}

int main() {
  cin >> n >> m;
  edges.resize(m);

  for (int i = 0; i < m; i++) {
    int a, b;
    ll w;
    cin >> a >> b >> w;
    edges[i] = {a, b, w};
  }

  vector<ll> dist;

  bool hasNegativeCycle = bellman(1, dist);

  if (hasNegativeCycle) {
    cout << "negative-weight cycle\n";
  } else {
    if (dist[n] == INF) {
      cout << "no path from 1 to " << n << "\n";
    } else {
      cout << "shortest path from 1 to " << n << " is: " << dist[n] << "\n";
    }
  }
}
