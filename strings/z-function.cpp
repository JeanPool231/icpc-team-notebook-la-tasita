#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(z[i - l], r - i);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

// ── 1. Pattern matching: find all occurrences of P in T ─────────────────────
// Concatenate P + '#' + T. Any position i in the T-part where z[i] == |P|
// corresponds to a match at T[i - |P| - 1].
vector<int> find_all(const string& P, const string& T) {
    string s = P + '#' + T;
    auto z = z_function(s);
    int m = P.size();
    vector<int> matches;
    for (int i = m + 1; i < (int)s.size(); i++)
        if (z[i] == m) matches.push_back(i - m - 1);
    return matches;
}

// ── 2. Shortest period of a string ──────────────────────────────────────────
// The shortest period p satisfies: s[0..n-p-1] == s[p..n-1],
// i.e. z[p] + p == n (the suffix at p matches the prefix and reaches the end).
int shortest_period(const string& s) {
    int n = s.size();
    auto z = z_function(s);
    for (int p = 1; p < n; p++)
        if (z[p] + p == n) return p;
    return n; // no period shorter than n
}

// ── 3. Longest border (prefix = suffix, proper) ─────────────────────────────
// A border of length k exists iff z[n-k] == k.
int longest_border(const string& s) {
    int n = s.size();
    auto z = z_function(s);
    for (int k = n - 1; k >= 1; k--)
        if (z[n - k] == k) return k;
    return 0;
}

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   string text = "abacaba", pattern = "aba";
//   for (int pos : find_all(pattern, text)) cout << pos << " ";
//   cout << "\nperiod = " << shortest_period(text) << "\n";
// }
