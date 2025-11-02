#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

int n,m;
vector<pair<int, int>> adj[MAXN];

void dijkstra(int s, vector<int> & d, vector<int> & p) {
  d.assign(n+1, INF);
  p.assign(n+1, -1);
  vector<bool> visited(n+1,0);

  d[s] = 0;
  using pii = pair<int, int>;
  priority_queue<pii, vector<pii>, greater<pii>> q;
  q.push({0, s});
  while (!q.empty()) {
    int v = q.top().second;
    q.pop();
    if(visited[v]) continue;
    visited[v] = 1;

    for (auto edge : adj[v]) {
      int to = edge.first;
      int len = edge.second;

      if (d[v] + len < d[to]) {
        d[to] = d[v] + len;
        p[to] = v;
        q.push({d[to], to});
      }
    }
  }
}

vector<int> restore_path(int s, int t, vector<int> const& p) {
  vector<int> path;

  for (int v = t; v != s; v = p[v])
    path.push_back(v);
  path.push_back(s);

  reverse(path.begin(), path.end());
  return path;
}


int main()
{
  cin >> n >> m;
  // adj.resize(n+1);
  while(m--) {
    int a,b,w;
    cin >> a >> b >> w;
    adj[a].push_back({b,w});
  }

  int str=1, target=n;

  vector<int> distance, path;

  dijkstra(str, distance,path);
  cout << distance[n] << '\n';
}
