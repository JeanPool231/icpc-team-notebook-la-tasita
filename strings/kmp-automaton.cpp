#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'

vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i-1];
    while (j > 0 && s[i] != s[j])
      j = pi[j-1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

void compute_automaton(string s, vector<vector<int>>& aut) {
  s += '#';
  int n = s.size();
  vector<int> pi = prefix_function(s);
  aut.assign(n, vector<int>(26));
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != s[i])
        aut[i][c] = aut[pi[i-1]][c];
      else
        aut[i][c] = i + ('a' + c == s[i]);
    }
  }
}

const int MAXN = 1e4+5;
const int MAXK = 1e3+5;
const int MOD = 1e9+7;


int n,k;
string pattern;
vector<vector<int>> aut;

long long binpow(long long a, long long b)
{
    long long result = 1;
    while (b) {
        if (b & 1)
            result = (result * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return result;
}

ll dp[MAXN][MAXK];
ll fdp(int pos, int state) {
  bool found = state == pattern.size();
  if(pos == n) {
    return  found;
  }

  ll &val = dp[pos][state];
  if(val != -1) return val;

  val = 0;

  if(found) {
    ll l = n-pos;
    return val = binpow(k, l);
  }

  for(int i = 0; i < k; i++) {
    val = (val + fdp(pos+1,aut[state][i])) % MOD;
  }

  return val;
}

void solve() {
  memset(dp, -1, sizeof dp);
  cin >> n >> k >> pattern;

  compute_automaton(pattern, aut);
  
  cout << fdp(0,0) << endl;
}

int main() {
  solve();
}
