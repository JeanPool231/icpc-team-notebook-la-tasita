// Combinatoria modular - Precalculo O(N + log MOD), consultas O(1)
// Requiere MOD primo y n < MAXN. Llamar precom() una vez antes de usar.

const ll MOD = 1e9 + 7;
const int MAXN = 2e6 + 5;
ll fac[MAXN], ifac[MAXN];

ll fastpow(ll b, ll e) {
    ll res = 1;
    b %= MOD;
    while (e > 0) {
        if (e & 1) res = res * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return res;
}

// Inverso modular por Fermat: a^(MOD-2) (MOD primo, a no multiplo de MOD)
ll inv(ll a) { return fastpow(a, MOD - 2); }

void precom() {
    fac[0] = 1;
    rep1(i, MAXN - 1) fac[i] = fac[i - 1] * i % MOD;
    ifac[MAXN - 1] = inv(fac[MAXN - 1]);
    repr(i, MAXN - 1) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}

// ─── 1. Combinaciones C(n, k) y Permutaciones P(n, k) ───────────────────────
ll nCr(int n, int k) {
    if (k < 0 || k > n || n < 0) return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

ll nPr(int n, int k) {
    if (k < 0 || k > n || n < 0) return 0;
    return fac[n] * ifac[n - k] % MOD;
}

// ─── 2. Stars and Bars ──────────────────────────────────────────────────────
// Formas de repartir m objetos identicos en n cajas (cajas pueden quedar vacias)
// = soluciones de x_1 + ... + x_n = m con x_i >= 0 = C(m + n - 1, n - 1)
ll starsBars(int m, int n) { return nCr(m + n - 1, n - 1); }

// Con cada caja >= 1 (x_i >= 1): C(m - 1, n - 1)
ll starsBarsPos(int m, int n) { return nCr(m - 1, n - 1); }

// ─── 3. Catalan: C_n = C(2n, n) / (n + 1) ───────────────────────────────────
// Parentesis balanceados, arboles binarios, caminos de Dyck (requiere 2n < MAXN)
ll catalan(int n) { return nCr(2 * n, n) * inv(n + 1) % MOD; }
