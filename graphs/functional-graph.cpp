#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

const int MAXN = 2e5+5;
const int LOG = 22;

int up[MAXN][LOG];
bool visited[MAXN];
bool on_stack[MAXN];
int next_node[MAXN];
int cycle[MAXN];
int cycle_length[MAXN];
int depth[MAXN];

int cycle_idx[MAXN];

void mark_cycle(int u, int id) {
  cycle[u] = id;
  depth[u] = 0;
  cycle_length[id]++;
  cycle_idx[u] = cycle_length[id];
  if(!cycle[next_node[u]])
    mark_cycle(next_node[u], id);
}

void dfs(int u) {
  visited[u] = 1;
  on_stack[u] = 1;

  int v = next_node[u];
  if(on_stack[v]) {
    mark_cycle(v, v);
  } else if(!visited[v]){
    dfs(v);
  }

  if(!cycle[u])
    depth[u] = depth[v] + 1;

  on_stack[u] = 0;
}

int jumpto(int u, int k) {
  int v = u;
  for(int i = 0; i < LOG; i++) {
    if((1 << i) & k) {
      v = up[v][i];
    }
  }
  return v;
}


int distcycle(int u, int v) {
  if(cycle_idx[u] < cycle_idx[v]) {
    return cycle_idx[v] - cycle_idx[u];
  }
  int turn = (cycle_length[cycle[u]] - cycle_idx[u] + 1) % cycle_length[cycle[u]];
  return turn + cycle_idx[v] - 1;
}

void solve() {
  int n,q;
  cin >> n >> q;

  for(int i = 1; i <= n; i++) {
    cin >> next_node[i];
    up[i][0] = next_node[i];
  }

  for(int j = 1; j < LOG; j++) {
    for(int i = 1; i <= n; i++) {
      up[i][j] = up[up[i][j-1]][j-1]; 
    }
  }

  for(int i = 1; i <= n; i++) {
    if(!visited[i]) dfs(i);
  }

  while(q--) {
    int u,v;
    cin >> u >> v;

    int cyu = cycle[u];
    int cyv = cycle[v];

    if(cyu == 0) {
      cyu = cycle[jumpto(u,depth[u])]; 
    }
    if(cyv == 0) {
      cyv = cycle[jumpto(v,depth[v])]; 
    }

    int a = u;
    int b = v;

    if(cyu != cyv) {
      cout << -1 << endl;
      continue;
    }

    if(cycle[u] == 0 && cycle[v] == 0) {
      if(depth[u] < depth[v]) {
        cout << -1 << endl;
        continue;
      }
      int diff = depth[u] - depth[v];
      if(jumpto(u,diff) != v) {
        cout << -1 << endl;
      } else {
        cout << diff << endl;
      }
      continue;
    }

    if(cycle[u] && cycle[v]) {
      cout << distcycle(u,v) << endl;
      continue;
    }

    if(cycle[u] == 0) {
      int steps = depth[u];
      steps += distcycle(jumpto(u,depth[u]), v);
      cout << steps << endl;
      continue;
    }

    if(cycle[v] == 0) {
      cout << -1 <<endl;
      continue;
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
