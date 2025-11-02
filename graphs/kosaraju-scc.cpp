#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long
#define ms(a, b) memset(a, b, sizeof(a))

const int INF = 1 << 30;
const int MAXN = 25;
const int MAXM = 25;

vector<bool> visited; // keeps track of which vertices are already visited

// runs depth first search starting at vertex v.
// each visited vertex is appended to the output vector when dfs leaves it.
void dfs(int v, vector<vector<int>> const& adj, vector<int> &output) {
  visited[v] = true;
  for (auto u : adj[v])
    if (!visited[u])
      dfs(u, adj, output);
  output.push_back(v);
}

// input: adj -- adjacency list of G
// output: components -- the strongly connected components in G
// output: adj_cond -- adjacency list of G^SCC (by root vertices)
void strongly_connected_components(vector<vector<int>> const& adj,
    vector<vector<int>> &components,
    vector<vector<int>> &adj_cond) {
  int n = (int)adj.size();
  components.clear();
  adj_cond.clear();

  // 1) Order the vertices by finish time in a first DFS.
  vector<int> order;
  visited.assign(n, false);
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i, adj, order);
    }
  }

  // 2) Reverse all edges to get the transpose graph.
  vector<vector<int>> adj_rev(n);
  for (int v = 0; v < n; v++) {
    for (int u : adj[v]) {
      adj_rev[u].push_back(v);
    }
  }

  // 3) Do a second DFS in descending order of finish times (from step 1).
  visited.assign(n, false);
  reverse(order.begin(), order.end());

  // this array will store the "root" (representative) of each SCC
  vector<int> roots(n, -1);

  for (auto v : order) {
    if (!visited[v]) {
      vector<int> component;
      dfs(v, adj_rev, component);
      // store the newly found component
      components.push_back(component);
      // the root is the minimum vertex in that component (arbitrary choice)
      int root = *min_element(begin(component), end(component));
      for (auto u : component) {
        roots[u] = root;
      }
    }
  }

  // 4) Build the condensation graph (SCC DAG).
  adj_cond.assign(n, {});
  for (int v = 0; v < n; v++) {
    for (auto u : adj[v]) {
      if (roots[v] != roots[u]) {
        adj_cond[roots[v]].push_back(roots[u]);
      }
    }
  }
}

void solve() {

  int n = 5, m = 5;
  vector<vector<int>> adj(n);

  vector<pair<int,int>> edges = {
    {0,1},
    {1,2},
    {2,0},
    {1,3},
    {3,4}
  };

  for (auto &e : edges) {
    adj[e.first].push_back(e.second);
  }

  vector<vector<int>> components, cond_graph;
  strongly_connected_components(adj, components, cond_graph);

  for (auto &comp : components) {
    sort(comp.begin(), comp.end());
  }

  cout << "Number of SCCs: " << (int)components.size() << "\n";
  for (int i = 0; i < (int)components.size(); i++) {
    cout << "SCC " << i << ": ";
    for (auto &v : components[i]) {
      cout << v << " ";
    }
    cout << "\n";
  }

  cout << "Condensation graph adjacency list:\n";
  // We'll print only non-empty adjacency to see edges
  for (int i = 0; i < (int)cond_graph.size(); i++) {
    if (!cond_graph[i].empty()) {
      cout << "root " << i << ": ";
      for (auto &v : cond_graph[i]) {
        cout << v << " ";
      }
      cout << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}

