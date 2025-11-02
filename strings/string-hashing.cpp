#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int MAXN = 1e5+5;
const int BASE = 31;
const int M = 1e9 + 7;

int pot[MAXN];

void compute_powers(int n) {
    int p_pow = 1;
    for (int i = 0; i < n; i++) {
        pot[i] = p_pow;
        p_pow = (p_pow * BASE) % M;
    }
}

vector<ll> compute_hash(string const& s) {
    int n = s.size();
    vector<ll> hash_values(n + 5);
    hash_values[0] = 0;
    for (int i = 1; i <= n; i++) {
        hash_values[i] = (hash_values[i - 1] * BASE + s[i - 1]) % M;
    }
    return hash_values;
}

ll get_hash(vector<ll> &hash_values, int a, int b) {
    return (hash_values[b] - (hash_values[a - 1] * pot[b - a + 1]) % M + M) % M;
}

int main() {
    string word = "ALLEY";
    compute_powers(word.size());
    vector<ll> hash = compute_hash(word);

    for (int i = 1; i <= word.size(); i++) {
        cout << hash[i] << ' ';
    }
    cout << endl;
    for (int i = 1; i <= word.size(); i++) {
        cout << word[i - 1] << ": " << get_hash(hash, i, i) << endl;
    }
    
    return 0;
}
