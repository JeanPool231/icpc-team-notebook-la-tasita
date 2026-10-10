// 0/1 Knapsack with Reconstruction - O(N * W)
// items: {peso, valor} -> retorna {max_valor, indices_tomados}
pair<ll, vi> knapsackReconstruction(const vii& items, int W) {
    int n = sz(items);
    vvll dp(n + 1, vll(W + 1, 0));
    rep(i, n) {
        int w = items[i].ff;
        ll v = items[i].ss;
        rep(j, W + 1) {
            dp[i + 1][j] = dp[i][j];
            if (j >= w) ckmax(dp[i + 1][j], dp[i][j - w] + v);
        }
    }
    vi taken;
    int cur_w = W;
    for (int i = n - 1; i >= 0; --i) {
        int w = items[i].ff;
        ll v = items[i].ss;
        if (cur_w >= w && dp[i + 1][cur_w] == dp[i][cur_w - w] + v) {
            taken.pb(i);
            cur_w -= w;
        }
    }
    reverse(all(taken));
    return {dp[n][W], taken};
}