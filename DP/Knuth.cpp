// Knuth's DP Optimization - O(N^2)
// Recurrencia: dp[i][j] = min_{i <= k < j} { dp[i][k] + dp[k+1][j] } + cost(i, j)
// Condicion de optimo: opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
// Requiere que cost(i, j) cumpla Quadrangle Inequality y Monotonicidad

ll knuthDP(const vll& arr) {
    int n = sz(arr);
    // Prefijos para calcular costo de rango en O(1)
    vll pref(n + 1, 0);
    rep(i, n) pref[i + 1] = pref[i] + arr[i];

    auto cost = [&](int i, int j) -> ll {
        return pref[j + 1] - pref[i];
    };

    vvll dp(n, vll(n, 0));
    vvi opt(n, vi(n, 0));

    // Casos base longitud 1
    rep(i, n) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }

    // Iterar por longitud del intervalo len = 2..N
    // O equivalentemente i de n-2 hasta 0, j de i+1 hasta n-1
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = LINF;
            ll c = cost(i, j);

            int l_opt = opt[i][j - 1];
            int r_opt = (i + 1 <= j) ? opt[i + 1][j] : j - 1;
            r_opt = min(r_opt, j - 1);

            for (int k = l_opt; k <= r_opt; ++k) {
                ll val = dp[i][k] + dp[k + 1][j] + c;
                if (val < dp[i][j]) {
                    dp[i][j] = val;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp[0][n - 1];
}
