#include <bits/stdc++.h>
using namespace std;

#define ll long long

namespace NTT {
    // MOD debe ser un primo de la forma c * 2^k + 1
    // 998244353 = 119 * 2^23 + 1. Raíz primitiva G = 3.
    const ll MOD = 998244353;
    const ll G = 3; // Raíz primitiva para MOD

    ll fast_pow(ll a, ll b) {
        ll res = 1;
        a %= MOD;
        while (b > 0) {
            if (b & 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }

    ll inv(ll a) {
        return fast_pow(a, MOD - 2); 
    }

    static vector<int> rev;
    static vector<ll> w;

    void precompute(int n) {
        if (rev.size() == n) return;
        int k = __builtin_ctz(n);
        rev.assign(n, 0);
        for (int i = 0; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }

        w.resize(n);
        w[0] = 1;
        ll g_n = fast_pow(G, (MOD - 1) / n);
        for(int i = 1; i < n; i++) {
            w[i] = (w[i - 1] * g_n) % MOD;
        }
    }

    void fft(vector<ll>& a, bool invertido) {
        int n = a.size();
        precompute(n);

        for (int i = 0; i < n; i++) {
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        for (int len = 1; len < n; len <<= 1) {
            int step = n / (2 * len);
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    ll u = a[i + j];
                    ll v = (a[i + j + len] * w[j * step]) % MOD;
                    
                    a[i + j] = (u + v) % MOD;
                    a[i + j + len] = (u - v + MOD) % MOD;
                }
            }
        }

        if (invertido) {
            reverse(a.begin() + 1, a.end());
            ll n_inv = inv(n);
            for (auto &x : a) {
                x = (x * n_inv) % MOD;
            }
        }
    }
} // namespace NTT

vector<ll> multiplicacion_polinomio_mod(const vector<ll>& A, const vector<ll>& B) {
    int n1 = A.size(), n2 = B.size();
    if (n1 == 0 || n2 == 0) return vector<ll>();

    int n = 1;
    while (n < n1 + n2 - 1) n = n << 1;
    
    vector<ll> fa(n), fb(n);
    for (int i = 0; i < n1; i++) fa[i] = (A[i] % NTT::MOD + NTT::MOD) % NTT::MOD;
    for (int i = 0; i < n2; i++) fb[i] = (B[i] % NTT::MOD + NTT::MOD) % NTT::MOD;

    NTT::fft(fa, false);
    NTT::fft(fb, false);
    
    for (int i = 0; i < n; i++) {
        fa[i] = (fa[i] * fb[i]) % NTT::MOD;
    }
    
    NTT::fft(fa, true);

    fa.resize(n1 + n2 - 1);
    return fa;
}


int main() {
    vector<ll> A = {1, 2, 3}; // 1 + 2x + 3x^2
    vector<ll> B = {2, 0, 1}; // 2 + 0x + 1x^2
    vector<ll> C = multiplicacion_polinomio_mod(A, B);
    return 0;
}
