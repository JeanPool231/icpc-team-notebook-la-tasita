#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e3+5;

int n;
ll d[MAXN][MAXN];

void floyd_warshall() {
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        if (d[i][k] + d[k][j] < d[i][j])
          d[i][j] = d[i][k] + d[k][j]; 
}

void solve() {
  int s, t;
  cin >> n;
  cin >> s >> t;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cin >> d[i][j];
      if(d[i][j] == -1) d[i][j] = INF;
    }
  }

  if(d[s][t] == INF)
    cout << "-1\n";
  else
   cout << d[s][t] << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  //cin >> t;
  while(t--)
    solve();
}
