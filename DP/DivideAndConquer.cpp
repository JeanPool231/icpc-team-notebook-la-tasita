// Divide and Conquer DP Optimization - O(K * N log N)
// Condicion: opt[k][i] <= opt[k][i+1] (e.g., Quadrangle Inequality)
// Recurrencia: dp[k][i] = min_{j < i} { dp[k-1][j] + cost(j, i) }

vll dp_prev, dp_curr;

// 1. Costo O(1) con formulas / prefijos (personalizar segun problema)
ll cost(int j, int i) {
    // Ejemplo: (pref[i] - pref[j])^2
    // ll s = pref[i] - pref[j];
    // return s * s;
    return 0;
}

// 2. Variante: Costo con Ventana Dinamica / Two Pointers estilo Mo
// int curL = 1, curR = 0; ll cur_cost = 0;
// void move_to(int L, int R) {
//     while (curR < R) add(++curR);
//     while (curL > L) add(--curL);
//     while (curR > R) remove(curR--);
//     while (curL < L) remove(curL++);
// }

void compute(int l, int r, int optL, int optR) {
    if (l > r) return;
    int mid = l + (r - l) / 2;
    int best_opt = -1;
    dp_curr[mid] = LINF;
    int limit = min(mid - 1, optR);

    for (int j = optL; j <= limit; ++j) {
        if (dp_prev[j] == LINF) continue;
        // Si se usa ventana dinamica: move_to(j + 1, mid);
        ll val = dp_prev[j] + cost(j, mid); // o dp_prev[j] + cur_cost;
        if (val < dp_curr[mid]) {
            dp_curr[mid] = val;
            best_opt = j;
        }
    }

    compute(l, mid - 1, optL, best_opt);
    compute(mid + 1, r, best_opt, optR);
}

// Resuelve para K particiones en un arreglo de tamaño N (1-indexed)
ll solveDCDP(int n, int k) {
    dp_prev.assign(n + 1, LINF);
    dp_curr.assign(n + 1, LINF);

    // Caso base k = 1
    dp_prev[0] = 0;
    rep1(i, n) dp_prev[i] = cost(0, i);

    // Transicion para k = 2..K
    for (int c = 2; c <= k; ++c) {
        compute(1, n, 0, n - 1);
        dp_prev = dp_curr;
    }
    return dp_prev[n];
}
