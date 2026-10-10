#include <bits/stdc++.h>
using namespace std;

// Single polynomial hash of a string
// hash(s) = s[0]*B^(n-1) + s[1]*B^(n-2) + ... + s[n-1]*B^0  (mod P)
// Equivalent iterative: hash = hash*B + s[i]

const long long MOD = 1e9 + 7;
const long long BASE = 131;

long long hash_str(const string& s) {
    long long h = 0;
    for (char c : s) {
        h = (h * BASE + c) % MOD;
    }
    return h;
}

// Precompute prefix hashes and powers for O(1) substring queries
struct HashTable {
    vector<long long> h, pw;
    long long mod, base;

    HashTable(const string& s, long long B = BASE, long long M = MOD)
        : h(s.size() + 1, 0), pw(s.size() + 1, 1), mod(M), base(B)
    {
        for (int i = 0; i < (int)s.size(); i++) {
            h[i + 1] = (h[i] * base + s[i]) % mod;
            pw[i + 1] = pw[i] * base % mod;
        }
    }

    // Hash of s[l..r] (0-indexed, inclusive)
    long long query(int l, int r) const {
        return (h[r + 1] - h[l] * pw[r - l + 1] % mod + mod) % mod;
    }
};

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   string s = "competitive";
//   HashTable h(s);
//   cout << hash_str(s) << "\n";
//   cout << h.query(0, 3) << "\n"; // hash of s[0..3]
// }
