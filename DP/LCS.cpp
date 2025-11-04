// https://leetcode.com/problems/longest-common-subsequence/submissions/1815539365/
#include <bits/stdc++.h>
using namespace std;

string s1, s2;
const int n = 1000;
int dp[n][n];

int LCS(int i, int j) {
    if (i < 0 || j < 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    if (s1[i] == s2[j]) dp[i][j] = 1 + LCS(i - 1, j - 1);
    else dp[i][j] = max(LCS(i-1,j), LCS(i,j-1));
    
    return dp[i][j];
}

string LCSReconstruccion() {
    int i = s1.size() - 1;
    int j = s2.size() - 1;
    string ans = "";

    while (i >= 0 && j >= 0) {
        if (s1[i] == s2[j]) {
            ans += s1[i];
            i--, j--;
        } 
        else {
            if (i > 0 && (j == 0 || dp[i - 1][j] >= dp[i][j - 1])) i--;
            else j--;
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    memset(dp,-1,sizeof(dp));
    s1 = "abcde";
    s2 = "ace";

    cout << LCS(s1.size() - 1, s2.size() - 1) << endl;
    cout << LCSReconstruccion() << endl;
}
