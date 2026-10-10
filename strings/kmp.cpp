#include <bits/stdc++.h>
using namespace std;

vector<int> buildFail(const string& P) {
    int m = P.size();
    vector<int> fail(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && P[i] != P[j]) j = fail[j - 1];
        if (P[i] == P[j]) j++;
        fail[i] = j;
    }
    return fail;
}

// ── Application 1: Count non-overlapping occurrences ─────────────────────────
int countNonOverlapping(const string& T, const string& P) {
    auto fail = buildFail(P);
    int count = 0, j = 0, m = P.size();
    for (char c : T) {
        while (j > 0 && c != P[j]) j = fail[j - 1];
        if (c == P[j]) j++;
        if (j == m) { count++; j = 0; } // reset instead of fail[m-1]
    }
    return count;
}

// ── Application 2: Shortest period of a string ───────────────────────────────
// The period of S is the smallest p such that S[i] == S[i % p] for all i.
// Using KMP: period = m - fail[m-1]   (if m % (m-fail[m-1]) == 0, else period = m)
int period(const string& S) {
    auto fail = buildFail(S);
    int m = S.size();
    int p = m - fail[m - 1];
    return (m % p == 0) ? p : m;
}

// ── Application 3: Concatenation search (good for multiple patterns) ─────────
// Search for P in T by building the "combined" string P + '#' + T,
// then checking where fail[i] == m in the combined string.
vector<int> kmpConcat(const string& T, const string& P) {
    string S = P + '#' + T;     // '#' is a separator not in the alphabet
    auto fail = buildFail(S);
    int m = P.size();
    vector<int> matches;
    for (int i = m + 1; i < (int)S.size(); i++)
        if (fail[i] == m)
            matches.push_back(i - 2 * m); // convert back to T-index
    return matches;
}

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   string text = "ababa", pattern = "aba";
//   cout << countNonOverlapping(text, pattern) << "\n";
//   cout << period(text) << "\n";
//   for (int pos : kmpConcat(text, pattern)) cout << pos << " ";
//   cout << "\n";
// }
