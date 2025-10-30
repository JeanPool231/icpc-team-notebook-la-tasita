// https://leetcode.com/problems/longest-increasing-subsequence/description/
#include <bits/stdc++.h>
using namespace std;

const int max_n = 100000;
int dp[max_n + 1];

int LIS(vector<int> arr) {
    int n = arr.size();
    memset(dp,0,sizeof(dp));

    int res = 0;
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1; 
        int valAc = arr[i];
        for (int j = 0; j < i; j++) {
            int valAn = arr[j];
            if (valAn < valAc) dp[i] = max(dp[i], dp[j] + 1);
        }
        res = max(res, dp[i]);
    }

    return res;
}

vector<int> LISReconstruccion(vector<int> arr) {
    int n = arr.size();
    vector<int> padre(n, -1); 

    int res = 0;
    int indiceMejorSecuencia = -1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1; 
        int valAc = arr[i];
        for (int j = 0; j < i; j++) {
            int valAn = arr[j];
            if (valAn < valAc && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                padre[i] = j;
            }
        }

        if (dp[i] > res) {
            res = dp[i];
            indiceMejorSecuencia = i;
        }
   
    }

    vector<int> secuencia;
    for (int i = indiceMejorSecuencia; i != -1; i = padre[i]) {
        secuencia.push_back(arr[i]);
    }
    reverse(secuencia.begin(), secuencia.end());

    return secuencia;
}

int main() {
    vector<int> nuevo = {1,3,6,7,9,4,10,5,6};
	cout << LIS(nuevo) << endl;

    vector<int> secuencia = LISReconstruccion(nuevo);
    for (int& val : secuencia) cout << val << " ";
}
