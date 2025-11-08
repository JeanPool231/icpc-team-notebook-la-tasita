#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define endl '\n'
using ll = long long;

const int MAXN = 200005;

// ---------- GLOBALS ----------
int n;
vector<int> adj[MAXN];
int sub[MAXN];         // subtree sizes
bool removed[MAXN];    // centroid removed flag
int parCentroid[MAXN]; // parent in centroid tree

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

void decompose(int u, int p = -1) {
    int total = dfs_size(u, -1);
    int c = find_centroid(u, -1, total);
    removed[c] = true;

    parCentroid[c] = (p == -1 ? c : p); // root centroid points to itself

    // Example: hook custom logic here (before recursing)
    // e.g., preprocess distances from c to other nodes in its component

    for (int v : adj[c]) {
        if (!removed[v])
            decompose(v, c);
    }
}

// ---------- MAIN ----------
int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(0);
    cout << "Centroid decomposition parent array:\n";
    for (int i = 0; i < n; i++)
        cout << i << " -> " << parCentroid[i] << endl;

    return 0;
}

