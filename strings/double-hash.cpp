#include <bits/stdc++.h>
using namespace std;

// Double hashing: use two independent hash functions
// to make collision probability negligible (~1/P1 * 1/P2)

struct DoubleHash {
    static const long long MOD1 = 1e9 + 7;
    static const long long MOD2 = 1e9 + 9;
    static const long long B1   = 131;
    static const long long B2   = 137;

    vector<long long> h1, h2, pw1, pw2;
    int n;

    DoubleHash(const string& s) : n(s.size()),
        h1(s.size()+1,0), h2(s.size()+1,0),
        pw1(s.size()+1,1), pw2(s.size()+1,1)
    {
        for (int i = 0; i < n; i++) {
            h1[i+1] = (h1[i] * B1 + s[i]) % MOD1;
            h2[i+1] = (h2[i] * B2 + s[i]) % MOD2;
            pw1[i+1] = pw1[i] * B1 % MOD1;
            pw2[i+1] = pw2[i] * B2 % MOD2;
        }
    }

    // Returns a pair (hash1, hash2) for s[l..r]
    pair<long long, long long> query(int l, int r) const {
        long long q1 = (h1[r+1] - h1[l] * pw1[r-l+1] % MOD1 + MOD1) % MOD1;
        long long q2 = (h2[r+1] - h2[l] * pw2[r-l+1] % MOD2 + MOD2) % MOD2;
        return {q1, q2};
    }

    bool equal(int l1, int r1, int l2, int r2) const {
        return query(l1, r1) == query(l2, r2);
    }
};

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   string s = "abracadabra";
//   DoubleHash h(s);
//   cout << h.query(0, 2).first << " " << h.query(0, 2).second << "\n";
//   cout << boolalpha << h.equal(0, 2, 7, 9) << "\n";
// }
