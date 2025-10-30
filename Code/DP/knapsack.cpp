// Source: https://atcoder.jp/contests/dp/tasks/dp_d
#include <bits/stdc++.h>
using namespace std;

const int MAX_W = 100001;
long long dp[MAX_W];
int W = MAX_W;

long long knapsack(const vector<pair<int, long long>>& items) {
    memset(dp, -1, sizeof(dp));
    int n = items.size();

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int w = items[i].first;
        long long v = items[i].second;

        for (int j = W; j >= w; j--) {
            if (dp[j - w] != -1) {
                dp[j] = max(dp[j], dp[j - w] + v);
            }
        }
    }
    
    long long max_v = 0;
    for (int j = 0; j <= W; j++) {
        max_v = max(max_v, dp[j]);
    }
    return max_v;
}

int main() {
	vector<pair<int, long long>> items = {{2,3},{3,5},{6,5}};
    cout << knapsack(items) << endl;
    return 0;
}