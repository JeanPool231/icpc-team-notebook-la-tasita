#include <bits/stdc++.h>
using namespace std;

/**
 * Given a list of N coins, their values (V1, V2, … , VN), and the total sum S. 
 * Find the minimum number of coins the sum of which is S
 * **/

int main() {

    const int INF = 1e9;
    vector<int> coins = {1,5,3,11};

    cout << "These are the coins: ";
    for (int c : coins) cout << c << " ";
    cout << endl;
    
    int s;
    cout << "Enter the value of S: ";
    cin >> s;

    vector<int> dp(s+1,INF); // dp saves the minimum number of coins to get a value i

    dp[0] = 0; // we need 0 coins to get 0 value

    for (int i = 1; i <= s; i++) {
        for (int c : coins) {
            if (i < c) continue;
            dp[i] = min(dp[i-c] + 1, dp[i]);
        }
    }

    cout << "The minimum number of coins to get " << s << " is: " << dp[s] << endl;

    return 0;
}
