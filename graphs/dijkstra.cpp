const ll INF = LLONG_MAX / 4;
struct Dijkstra {
  int n;
  vector<vector<pair<int,ll>>> g;
  vector<ll> d;
  vector<int> par;
  Dijkstra(int n) : n(n), g(n) {}
  void add_edge(int a, int b, ll w) { g[a].push_back({b,w}); } // directed
  void add_undirected(int a, int b, ll w) { add_edge(a,b,w); add_edge(b,a,w); }
  void run(const vector<int>& src) { // multi-source
    d.assign(n,INF); par.assign(n,-1);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
    for (int s : src) { d[s] = 0; pq.push({0,s}); }
    while (!pq.empty()) {
      auto [du,u] = pq.top(); pq.pop();
      if (du > d[u]) continue; // stale entry
      for (auto [v,w] : g[u])
        if (d[u]+w < d[v]) { d[v] = d[u]+w; par[v] = u; pq.push({d[v],v}); }
    }
  }
  void run(int s) { run(vector<int>{s}); }
  vector<int> path(int t) { // s -> t, empty if unreachable
    vector<int> p;
    if (d[t] >= INF) return p;
    for (; t >= 0; t = par[t]) p.push_back(t);
    reverse(p.begin(),p.end());
    return p;
  }
};
