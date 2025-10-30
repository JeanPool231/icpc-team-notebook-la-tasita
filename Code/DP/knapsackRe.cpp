#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1001;
const int MAX_W = 1001;

int N, W;
long long dp[MAX_N][MAX_W];
vector<pair<int, long long>> items;

long long knapsack(int i, int w_rem) {
    if (i == N || w_rem == 0) {
        return 0;
    }
    if (dp[i][w_rem] != -1) {
        return dp[i][w_rem];
    }

    int w = items[i].first;
    long long v = items[i].second;

    long long res = knapsack(i + 1, w_rem);
    if (w_rem >= w) {
        res = max(res, v + knapsack(i + 1, w_rem - w));
    }

    return dp[i][w_rem] = res;
}

vector<pair<int, long long>> knapsackReconstruccion() {
    vector<pair<int, long long>> tomados;
    int w_rem = W;

    for (int i = 0; i < N; i++) {
        int w = items[i].first;
        long long v = items[i].second;

        if (knapsack(i + 1, w_rem) == dp[i][w_rem]) {
            continue;
        } 

        else if (w_rem >= w && (v + knapsack(i + 1, w_rem - w) == dp[i][w_rem])) {
            tomados.push_back(items[i]);
            w_rem -= w;
        }
    }
    return tomados;
}


int main() {
    memset(dp, -1, sizeof(dp));
    items = {{3, 30}, {4, 50}, {5, 60}};
    W = 8;
    N = items.size();
    cout << knapsack(0, W) << endl;

    vector<pair<int, long long>> res = knapsackReconstruccion();
    cout << "Items tomados:" << endl;
    for (auto& item : res) {
        cout << "Peso: " << item.first << ", Valor: " << item.second << endl;
    }
}