// Longest Common Subsequence & Reconstruction - O(N * M)
pair<int, string> LCS(const string& s1, const string& s2) {
    int n = sz(s1), m = sz(s2);
    vvi dp(n + 1, vi(m + 1, 0));
    rep(i, n) rep(j, m) {
        if (s1[i] == s2[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
        else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
    }
    string ans = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            ans += s1[i - 1];
            i--; j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(all(ans));
    return {dp[n][m], ans};
}

