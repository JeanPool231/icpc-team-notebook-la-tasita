#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const long long BASE = 131;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// Compute hash of every substring of length k in O(n) total
vector<long long> rolling_hash(const string& s, int k) {
    int n = s.size();
    if (n < k) return {};

    vector<long long> result;
    long long h = 0;
    long long base_k = power(BASE, k - 1, MOD);  // B^(k-1)

    // Initial window [0, k-1]
    for (int i = 0; i < k; i++)
        h = (h * BASE + s[i]) % MOD;
    result.push_back(h);

    for (int i = 1; i + k - 1 < n; i++) {
        // Remove s[i-1], add s[i+k-1]
        h = (h - (long long)s[i - 1] * base_k % MOD + MOD) % MOD;
        h = (h * BASE + s[i + k - 1]) % MOD;
        result.push_back(h);
    }

    return result;
}

// Find all occurrences of pattern p in text t using rolling hash
vector<int> rabin_karp(const string& t, const string& p) {
    int n = t.size(), m = p.size();
    long long ph = 0;
    for (char c : p) ph = (ph * BASE + c) % MOD;

    vector<long long> th = rolling_hash(t, m);
    vector<int> matches;
    for (int i = 0; i < (int)th.size(); i++)
        if (th[i] == ph)
            if (t.substr(i, m) == p)  // confirm match (avoid hash collision)
                matches.push_back(i);
    return matches;
}

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   string text = "abacaba", pattern = "aba";
//   for (int pos : rabin_karp(text, pattern)) cout << pos << " ";
//   cout << "\n";
// }
