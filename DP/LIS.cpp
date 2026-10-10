// O(N^2) Longest Increasing Subsequence
int LIS(const vi& arr) {
    int n = sz(arr);
    vi dp(n, 1);
    int res = 0;
    rep(i, n) {
        rep(j, i) {
            if (arr[j] < arr[i]) ckmax(dp[i], dp[j] + 1);
        }
        ckmax(res, dp[i]);
    }
    return res;
}

vi LISReconstruccion(const vi& arr) {
    int n = sz(arr);
    vi dp(n, 1), padre(n, -1);
    int res = 0, best_idx = -1;

    rep(i, n) {
        rep(j, i) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                padre[i] = j;
            }
        }
        if (dp[i] > res) {
            res = dp[i];
            best_idx = i;
        }
    }

    vi secuencia;
    for (int i = best_idx; i != -1; i = padre[i]) {
        secuencia.pb(arr[i]);
    }
    reverse(all(secuencia));
    return secuencia;
}

