#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

vector<int> adj[MAXN];
vector<int> topo;

int n,m;

void dfs(int u, vector<int> &visited) {
  visited[u] = 1;
  for (int &v : adj[u]) {
    if (!visited[v]) 
      dfs(v, visited);
    else if(visited[v] == 1){
      cout << "IMPOSSIBLE\n";
      exit(0);
    }
  }
  visited[u] = 2;
  topo.push_back(u);
}

void topological_sort() {
  topo.clear();
  vector<int> visited(n+1,0);

  for (int i = 1; i <= n; i++) 
    if (!visited[i])
      dfs(i, visited);

  reverse(topo.begin(), topo.end());
}

void solve() {
  cin >> n >> m;
  for(int i = 0; i <= n; i++) adj[i].clear();
  while(m--) {
    int a,b;
    cin >> a >> b;
    adj[a].push_back(b);
  }
  topological_sort();
  for (int x : topo) cout << x << " ";
  cout << "\n";
}

int main() {
  int t = 1;
  // cin >> t;
  while(t--) 
    solve();
}


