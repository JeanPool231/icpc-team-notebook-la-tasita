// https://leetcode.com/problems/tallest-billboard/description/
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2501;
int diferencia[2][MAX_N];

int knapsackDiferencia(const vector<int>& arr) {
    int n = arr.size();
    memset(diferencia,-1,sizeof(diferencia));
    diferencia[0][0] = 0;

    for (int i = 0; i < n; i++) {
        int ahora = arr[i];
        int actual = i & 1;
        int siguiente = actual ^ 1;

        fill(diferencia[siguiente], diferencia[siguiente] + MAX_N, -1);
        
        for (int valor = 0; valor < MAX_N; valor++) {
            if (diferencia[actual][valor] == -1) continue;

            diferencia[siguiente][valor] = max(
                diferencia[siguiente][valor],
                diferencia[actual][valor]
            );

            int nuevaDiferenciaMayor = valor + ahora;
            if (nuevaDiferenciaMayor < MAX_N) {
                diferencia[siguiente][nuevaDiferenciaMayor] = max(
                    diferencia[siguiente][nuevaDiferenciaMayor],
                    diferencia[actual][valor]
                );
            }

            int nuevaDiferenciaMenor = abs(valor - ahora);
            int nuevaAltura = diferencia[actual][valor] + min(valor, ahora);
            diferencia[siguiente][nuevaDiferenciaMenor] = max(
                diferencia[siguiente][nuevaDiferenciaMenor],
                nuevaAltura
            );
        }
    }

    return diferencia[n & 1][0];
}

int main() {
    vector<int> roads = {1,2,3,6};
    cout << knapsackDiferencia(roads) << endl;
}