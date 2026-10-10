// DP Optimization with Data Structures (Segment Tree / Fenwick) - O(N log N)
// Optimiza transiciones: dp[i] = max_{j < i, L <= val[j] <= R} { dp[j] } + cost[i]

// ─── 1. Compresion de Coordenadas ───────────────────────────────────────────
// Mapea valores arbitrarios a [0, sz(vals)-1]
template<class T>
vi compress(const vector<T>& a) {
    vector<T> vals = a;
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    vi res(sz(a));
    rep(i, sz(a)) {
        res[i] = lower_bound(all(vals), a[i]) - vals.begin();
    }
    return res;
}

// ─── 2. Segment Tree para Maximos en Rango ──────────────────────────────────
struct SegTreeDP {
    int n;
    vll tree;
    SegTreeDP(int n) : n(n), tree(4 * n, 0) {}

    void update(int pos, ll val, int node, int l, int r) {
        if (l == r) {
            ckmax(tree[node], val);
            return;
        }
        int mid = l + (r - l) / 2;
        if (pos <= mid) update(pos, val, 2 * node, l, mid);
        else update(pos, val, 2 * node + 1, mid + 1, r);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    void update(int pos, ll val) { update(pos, val, 1, 0, n - 1); }

    ll query(int ql, int qr, int node, int l, int r) {
        if (ql > r || qr < l) return 0; // valor neutro
        if (ql <= l && r <= qr) return tree[node];
        int mid = l + (r - l) / 2;
        return max(query(ql, qr, 2 * node, l, mid),
                   query(ql, qr, 2 * node + 1, mid + 1, r));
    }
    ll query(int ql, int qr) {
        if (ql > qr) return 0;
        return query(ql, qr, 1, 0, n - 1);
    }
};

// ─── 3. Fenwick de Maximos (O(log N) - Solo para Prefijos [0..idx]) ─────────
struct BITMax {
    int n;
    vll bit;
    BITMax(int n) : n(n), bit(n + 1, 0) {}
    void update(int i, ll val) {
        for (++i; i <= n; i += i & -i) ckmax(bit[i], val);
    }
    ll query(int i) { // maximo en [0..i]
        ll res = 0;
        for (++i; i > 0; i -= i & -i) ckmax(res, bit[i]);
        return res;
    }
};

// Ejemplo de uso (LIS Ponderado / Flowers):
// vi comp = compress(alturas);
// SegTreeDP st(sz(comp));
// rep(i, n) {
//     ll best_prev = st.query(0, comp[i] - 1);
//     st.update(comp[i], best_prev + bellezas[i]);
// }
// ll ans = st.query(0, sz(comp) - 1);
