// Two Pointers & Sliding Window Aggregation (SWAG)

// 1. Sliding Window Estandar - O(N)
// Ejemplo: Maxima longitud de subarray con condicion monotona
int slidingWindow(const vi& a, int k) {
    int n = sz(a), ans = 0, l = 0;
    // Estado de la ventana (ej. frecuencias, suma)
    // vi freq(MAX_VAL, 0); int distinct = 0;

    rep(r, n) {
        // add(a[r]);
        // while (!valid()) { remove(a[l++]); }
        ckmax(ans, r - l + 1);
    }
    return ans;
}

// 2. SWAG (Sliding Window Aggregation) - O(1) amortizado por push/pop/query
// Permite operaciones asociativas NO reversibles (ej: min, max, gcd, matrix mul)
template<class T>
struct SWAG {
    struct Node {
        T val, agg;
    };
    stack<Node> s1, s2;

    T op(T a, T b) { return min(a, b); } // Cambiar operacion (gcd, max, +, etc.)

    bool empty() { return s1.empty() && s2.empty(); }
    int size() { return sz(s1) + sz(s2); }

    void push(T val) {
        T agg = s2.empty() ? val : op(s2.top().agg, val);
        s2.push({val, agg});
    }

    void pop() {
        if (s1.empty()) {
            while (!s2.empty()) {
                T val = s2.top().val;
                s2.pop();
                T agg = s1.empty() ? val : op(val, s1.top().agg);
                s1.push({val, agg});
            }
        }
        s1.pop();
    }

    T query() {
        if (empty()) return 0; // valor neutro
        if (s1.empty()) return s2.top().agg;
        if (s2.empty()) return s1.top().agg;
        return op(s1.top().agg, s2.top().agg);
    }
};
