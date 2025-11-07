#include "bits/stdc++.h"
using namespace std;

using ll = long long;
using ld = long double;
#define sz(v) ((int)((v).size()))

const int MAXN = 100005;

int n;
vector<int> adj[MAXN];
int sub[MAXN];
bool removed[MAXN]; 
int parCentroid[MAXN];
vector<vector<pair<int,int>>> elements(MAXN);

vector<vector<pair<int,int>>> sufix(MAXN); 
#define linea() cerr << "---------------------------" << '\n'
int dfs_size(int u, int p) {
    sub[u] = 1;
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        sub[u] += dfs_size(v, u);
    }
    return sub[u];
}

int find_centroid(int u, int p, int total) {
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sub[v] > total / 2)
            return find_centroid(v, u, total);
    }
    return u;
}
void bfs(int node) {
    map<int, int> dist;
    queue<int> q;
    q.push(node);
    elements[node].push_back({node, 0});
    while (!q.empty()) {
        auto l = q.front();
        q.pop();
        for (auto& x : adj[l]) {
            if (dist[x] == 0 && !removed[x] && x != node) {
                dist[x] = dist[l] + 1;
                q.push(x);
                elements[node].push_back({x, dist[x]});
            }
        }
    }
    
    sort(elements[node].begin(), elements[node].end());

    sufix[node].resize(sz(elements[node]) + 1);

    pair<int, int> otro {1e9, 1e9};
    for (int i = sz(elements[node]) - 1; i >= 0; i--) {
        if (otro.second > elements[node][i].second) {
            otro = elements[node][i];
        }
        else if (otro.second == elements[node][i].second) {
            if (otro.first > elements[node][i].first) otro = elements[node][i];
        }
        sufix[node][i] = otro;
    }
}
void decompose(int u, int p = -1) {
    int total = dfs_size(u, -1);
    int c = find_centroid(u, -1, total);
    bfs(c);
    removed[c] = true;

    parCentroid[c] = (p == -1 ? c : p); // root centroid points to itself

    // Example: hook custom logic here (before recursing)
    // e.g., preprocess distances from c to other nodes in its component

    for (int v : adj[c]) {
        if (!removed[v])
            decompose(v, c);
    }
}
int bs(vector<pair<int, int>>& v, int target) {
    int low = 0, high = sz(v) - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (v[mid].first > target) {
            ans = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return ans;
}
int dist(vector<pair<int, int>>& v, int target) {
    int low = 0, high = sz(v) - 1;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (v[mid].first == target) {
            return mid;
        }
        else if (v[mid].first < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(1);
    for (int i = 1; i < n; i++) {
        int aux = i;
        int ori = aux;
        pair<int, int> res = {1e9, 1e9};
        bool ya = false;
        do {
            int it = bs(elements[aux], ori);
            if (it == -1) {
                aux = parCentroid[aux];
                linea();
                continue;
            }
            pair<int, int> ans = sufix[aux][it];
            int it2 = dist(elements[aux], ori);
            ans.second += elements[aux][it2].second;
            if (ans.second < res.second) {
                res = ans;
            }
            else if (ans.second == res.second) {
                if (ans.first < res.first) {
                    res = ans;
                }
            }
            aux = parCentroid[aux];
            linea();
            if (ya) break;
            if (parCentroid[aux] == aux) ya = true;
        } while (true);
        cout << res.first << ' ';
    }
    cout << n << '\n';
    
    return 0;
}
