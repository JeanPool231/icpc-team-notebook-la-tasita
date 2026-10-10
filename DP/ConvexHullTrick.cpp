// Convex Hull Trick (CHT) - O(1) amortizado por insercion y query
// Optimiza: dp[i] = min/max ( m_j * x_i + c_j )
// Condicion: Pendientes 'm' insertadas en orden MONOTONO (creciente/decreciente).
// Para queries 'x' monotonos: query() usa dos punteros O(1).
// Para queries 'x' arbitrarios: query_bin() usa busqueda binaria O(log N).

struct Line {
    ll m, c;
    ll eval(ll x) const { return m * x + c; }
};

// CHT para MINIMIZAR (m decreciente, queries x crecientes)
// Para MAXIMIZAR: invertir signos o usar m creciente y cambiar condicion is_bad
struct CHT {
    vector<Line> hull;
    int ptr = 0;

    // Retorna true si l2 es redundante entre l1 y l3
    bool is_bad(const Line& l1, const Line& l2, const Line& l3) {
        // Interseccion(l1, l2) >= Interseccion(l2, l3) usando __int128 para evitar overflow
        return (__int128)(l1.c - l2.c) * (l3.m - l2.m) >= (__int128)(l2.c - l3.c) * (l2.m - l1.m);
    }

    void add(ll m, ll c) {
        Line l = {m, c};
        while (sz(hull) >= 2 && is_bad(hull[sz(hull) - 2], hull.back(), l)) {
            hull.pop_back();
        }
        hull.pb(l);
        if (ptr >= sz(hull)) ptr = sz(hull) - 1;
    }

    // Query O(1) amortizado (requiere x monotonamente creciente)
    ll query(ll x) {
        if (hull.empty()) return LINF;
        while (ptr + 1 < sz(hull) && hull[ptr + 1].eval(x) <= hull[ptr].eval(x)) {
            ++ptr;
        }
        return hull[ptr].eval(x);
    }

    // Query O(log N) para x arbitrarios (no requiere que x sea monotono)
    ll query_bin(ll x) {
        if (hull.empty()) return LINF;
        int l = 0, r = sz(hull) - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (hull[mid + 1].eval(x) <= hull[mid].eval(x)) l = mid + 1;
            else r = mid;
        }
        return hull[l].eval(x);
    }
};
