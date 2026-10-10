#include <bits/stdc++.h>
using namespace std;

vector<int> suffix_array(const string& s) {
    int n = s.size();
    vector<int> sa(n), rank_(n), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rank_[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        auto key = [&](int i) -> pair<int,int> {
            return {rank_[i], i + k < n ? rank_[i + k] : -1};
        };
        sort(sa.begin(), sa.end(), [&](int a, int b){ return key(a) < key(b); });
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + (key(sa[i]) != key(sa[i-1]));
        rank_ = tmp;
        if (rank_[sa[n-1]] == n-1) break;
    }
    return sa;
}

vector<int> kasai_lcp(const string& s, const vector<int>& sa) {
    int n = sa.size();
    vector<int> rank_(n), lcp(n, 0);
    for (int i = 0; i < n; i++) rank_[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank_[i] > 0) {
            int j = sa[rank_[i] - 1];
            while (i + h < n && j + h < n && s[i+h] == s[j+h]) h++;
            lcp[rank_[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}

// ── 1. Pattern search: O(M log N) ───────────────────────────────────────────
// Binary search on SA: all matches are a contiguous range [lo, hi).
pair<int,int> search_range(const string& s, const vector<int>& sa, const string& P) {
    int n = sa.size(), m = P.size();
    int lo = (int)(lower_bound(sa.begin(), sa.end(), 0, [&](int a, int) {
        return s.compare(a, m, P) < 0;
    }) - sa.begin());
    int hi = (int)(upper_bound(sa.begin(), sa.end(), 0, [&](int, int a) {
        return s.compare(a, m, P) > 0;
    }) - sa.begin());
    return {lo, hi};
}

// ── 2. Count distinct substrings ────────────────────────────────────────────
// Total substrings = N*(N+1)/2. Subtract duplicates counted by LCP array.
long long distinct_substrings(const string& s) {
    auto sa  = suffix_array(s);
    auto lcp = kasai_lcp(s, sa);
    int n = s.size();
    long long total = (long long)n * (n + 1) / 2;
    for (int v : lcp) total -= v;
    return total;
}

// ── 3. Longest repeated substring ───────────────────────────────────────────
// The maximum value in the LCP array.
string longest_repeated(const string& s) {
    auto sa  = suffix_array(s);
    auto lcp = kasai_lcp(s, sa);
    int best = *max_element(lcp.begin(), lcp.end());
    int idx  = max_element(lcp.begin(), lcp.end()) - lcp.begin();
    return best > 0 ? s.substr(sa[idx], best) : "";
}

// Ejemplo de uso anterior (main comentado para compilar con la plantilla):
// int main() {
//   string s = "banana";
//   vector<int> sa = suffix_array(s);
//   for (int pos : sa) cout << pos << " ";
//   cout << "\ndistinct substrings = " << distinct_substrings(s) << "\n";
//   cout << "longest repeated = " << longest_repeated(s) << "\n";
// }
