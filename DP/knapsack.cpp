// 0/1 Knapsack - O(N * W)
// items: {peso, valor}
ll knapsack(const vii& items, int W) {
    vll dp(W + 1, -1);
    dp[0] = 0;
    each(item, items) {
        int w = item.ff;
        ll v = item.ss;
        for (int j = W; j >= w; --j) {
            if (dp[j - w] != -1) {
                ckmax(dp[j], dp[j - w] + v);
            }
        }
    }
    ll max_v = 0;
    rep(j, W + 1) ckmax(max_v, dp[j]);
    return max_v;
}