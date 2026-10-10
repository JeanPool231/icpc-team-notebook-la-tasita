// Subset Sum with Equal Partition / Difference DP - O(N * sum)
// Encuentra la máxima altura igual de dos subconjuntos disjuntos (Tallest Billboard)
int knapsackDiferencia(const vi& arr) {
    int sum = 0;
    each(x, arr) sum += x;
    vi dp(sum + 1, -1);
    dp[0] = 0;

    each(h, arr) {
        vi next_dp = dp;
        rep(d, sum + 1) {
            if (dp[d] < 0) continue;
            // 1. No usar h (ya cubierto por next_dp = dp)
            // 2. Añadir al lado mayor
            if (d + h <= sum) ckmax(next_dp[d + h], dp[d]);
            // 3. Añadir al lado menor
            int diff = abs(d - h);
            ckmax(next_dp[diff], dp[d] + min(d, h));
        }
        dp = move(next_dp);
    }
    return dp[0];
}
