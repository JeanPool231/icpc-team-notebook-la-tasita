// https://cses.fi/problemset/task/1159/
#include <bits/stdc++.h>
using namespace std;

const int MAX_W = 100001;
int dp[MAX_W];
int W;

int knapsack(const vector<pair<int, int>>& items) {
    memset(dp, -1, sizeof(dp));
    int n = items.size();
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        int w = items[i].first;
        int v = items[i].second;

        for (int j = W; j >= w; j--) {
            if (dp[j - w] != -1) {
                dp[j] = max(dp[j], dp[j - w] + v);
            }
        }
    }

    int max_v = 0;
    for (int j = 0; j <= W; j++) {
        max_v = max(max_v, dp[j]);
    }
    return max_v;
}

void res(const vector<int>& pesos, const vector<int>& valores, const vector<int>& copias) {
    int n = pesos.size();
    vector<pair<int, int>> items;
    for (int i = 0; i < n; i++) {
        int k = copias[i];
        int b = 1;
        while (k > 0) {
            int num = min(k, b);
            items.push_back({pesos[i] * num, valores[i] * num});
            k -= num;
            b *= 2;
        }
    }
    cout << knapsack(items) << endl;
}

int main() {
    vector<int> pesos = {2, 6, 3};
    vector<int> valores = {8, 5, 4};
    vector<int> copias = {3, 5, 2};
    res(pesos, valores, copias);
}