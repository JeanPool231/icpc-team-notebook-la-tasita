// https://leetcode.com/problems/longest-increasing-subsequence/description/
#include <bits/stdc++.h>
using namespace std;

int LISFast(vector<int> arr) {
    int n = arr.size();
    vector<int> res;
    res.push_back(arr[0]);

    for (int i = 1; i < n; i++) {
        if (arr[i] > res.back()) {
            res.push_back(arr[i]);
        } else { 
            auto it = lower_bound(res.begin(),res.end(),arr[i]);
            int busca = it - res.begin();
            res[busca] = arr[i];
        }
    }

    return res.size();
}

vector<int> LISFastReconstruccion(vector<int> arr) {
    int n = arr.size();
    vector<int> res;
    vector<int> resIndex;
    vector<int> padre(n, - 1);

    for (int i = 0; i < n; i++) {
        int x = arr[i];
        auto it = lower_bound(res.begin(), res.end(), x);
        int pos = it - res.begin();

        if (it == res.end()) {
            res.push_back(x);
            resIndex.push_back(i);
        } else {
            *it = x;
            resIndex[pos] = i;
        }

        if (pos > 0)
            padre[i] = resIndex[pos - 1];
    }

    vector<int> lis;
    int idx = resIndex.back();
    while (idx != -1) {
        lis.push_back(arr[idx]);
        idx = padre[idx];
    }
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    vector<int> nuevo = {1,3,6,7,9,4,10,5,6};
	cout << LISFast(nuevo) << endl;

    vector<int> reconstruccion = LISFastReconstruccion(nuevo);
    for (int& val : reconstruccion) cout << val << " ";
}
