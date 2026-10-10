// Expected Value & Probability (Esperanza Matematica)
// 1. Linealidad de la Esperanza: E[X + Y] = E[X] + E[Y] (siempre valido, aun dependientes)
// 2. Variable indicadora: E[I_A] = P(A)
// 3. Ensayos geometricos (primer exito con prob p): E = 1/p
// 4. Coupon Collector (recolectar n cupones): E = n * sum_{i=1}^n (1/i) = n * H_n

// ─── Sistema Lineal para Esperanza en Grafos de Estados / Markov ─────────────
// E[u] = 1 + sum_{v} P(u -> v) * E[v]
// Se transforma en: E[u] - sum_{v} P(u -> v) * E[v] = 1 (con E[target] = 0)
// Resuelto con Eliminacion Gaussiana O(N^3)

const ld EPS = 1e-11;

// Retorna 1 si tiene solucion unica, 0 si no o infinitas. Solucion en ans.
int gauss(vector<vector<ld>> a, vector<ld>& ans) {
    int n = sz(a), m = sz(a[0]) - 1;
    vi where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (fabsl(a[i][col]) > fabsl(a[sel][col])) sel = i;
        if (fabsl(a[sel][col]) < EPS) continue;
        for (int i = col; i <= m; ++i) swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i) {
            if (i != row) {
                ld c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
    }
    ans.assign(m, 0);
    rep(i, m) {
        if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
    }
    rep(i, n) {
        ld sum = 0;
        rep(j, m) sum += ans[j] * a[i][j];
        if (fabsl(sum - a[i][m]) > EPS) return 0;
    }
    return 1;
}

// Construccion de matriz para n estados (0..n-1), absorbiendo en target
// adj[u] = lista de {v, prob}
vector<ld> expectedSteps(int n, int target, const vector<vector<pair<int, ld>>>& adj) {
    vector<vector<ld>> A(n, vector<ld>(n + 1, 0));
    rep(u, n) {
        if (u == target) {
            A[u][u] = 1;
            A[u][n] = 0; // E[target] = 0
            continue;
        }
        A[u][u] = 1.0;
        A[u][n] = 1.0; // sumatoria de costo/paso base = 1
        for (auto& edge : adj[u]) {
            int v = edge.ff;
            ld p = edge.ss;
            A[u][v] -= p;
        }
    }
    vector<ld> E;
    gauss(A, E);
    return E;
}
