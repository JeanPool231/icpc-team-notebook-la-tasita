// Bounded Knapsack (Binary Splitting) - O(W * sum(log K))
ll knapsackBounded(const vi& pesos, const vll& valores, const vi& copias, int W) {
    vii items;
    int n = sz(pesos);
    rep(i, n) {
        int k = copias[i], b = 1;
        while (k > 0) {
            int num = min(k, b);
            items.eb(pesos[i] * num, valores[i] * num);
            k -= num;
            b *= 2;
        }
    }
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
    ll ans = 0;
    rep(j, W + 1) ckmax(ans, dp[j]);
    return ans;
}