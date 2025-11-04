// https://leetcode.com/problems/maximum-subarray/submissions/1815546613/
#include <bits/stdc++.h>
using namespace std;

const int max_n = 100001;
int dp[max_n];

int maximumSub(vector<int>& arr) {
    memset(dp,0,sizeof(dp));
    int n = arr.size();

    for (int i = 1; i <= n; i++) {
        int& valor = arr[i - 1];
        dp[i] = max(valor, dp[i - 1] + valor);
    }

    int maximo = -1000000000;
    for (int i = 1; i <= n; i++) {
        maximo = max(maximo, dp[i]);
    }
    return maximo;
}

int main() {
    vector<int> valores = {-2,1,-3,4,-1,2,1,-5,4};
    cout << maximumSub(valores);
}
