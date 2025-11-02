#include <bits/stdc++.h>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define ll long long

const int INF = 1 << 30;
const int MAXN = 1e5+5;

int MAXL;
int n;

int arr[MAXN];
vector<vector<int>> st; // sparse table

void preprocess() {
  MAXL = ceil(log2(n));

  st.assign(n, vector<int>(MAXL + 1, INF));
  
  for(int i = 0; i < n; i++) 
    st[i][0] = arr[i];

  for(int j = 1; j <= MAXL; j++) {
    for (int i = 0; i + (1 << j) - 1 < n; i++) {
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
}


void solve() {
  cin >> n;
  for(int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  preprocess();

  int q; cin >> q;
  while(q--){
    int l,r;
    cin >> l >> r;
    int k = floor(log2(r - l + 1));
    cout << min(st[l][k], st[r - (1 << k) + 1][k]) << endl;
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
