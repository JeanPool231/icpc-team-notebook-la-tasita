// Digit DP Template - Complejidad O(Longitud * Estados * 10)
// Estados tipicos: (pos, tight, leading_zero, estado_personalizado)

// ─── 1. Enfoque Estandar f(R) - f(L - 1) ────────────────────────────────────
string S;
ll memo[20][2][2][100]; // Ajustar dimensiones del estado personalizado

ll digitDP(int pos, bool tight, bool lz, int state) {
    if (pos == sz(S)) {
        // Retornar 1 si el 'state' es valido, 0 si no
        return 1;
    }
    ll& ans = memo[pos][tight][lz][state];
    if (ans != -1) return ans;

    ans = 0;
    int limit = tight ? (S[pos] - '0') : 9;

    for (int dig = 0; dig <= limit; ++dig) {
        bool next_tight = tight && (dig == limit);
        bool next_lz = lz && (dig == 0);
        
        // Actualizar estado personalizado (ejemplo: suma de digitos, bitmask, mod, etc.)
        int next_state = next_lz ? 0 : (state + dig);

        ans += digitDP(pos + 1, next_tight, next_lz, next_state);
        // Si pide modulo: ans %= MOD;
    }
    return ans;
}

ll countValid(ll n) {
    if (n < 0) return 0;
    S = to_string(n);
    memset(memo, -1, sizeof(memo));
    return digitDP(0, true, true, 0);
}

// Rango [L, R]
ll solveRange(ll L, ll R) {
    return countValid(R) - countValid(L - 1);
}

// ─── 2. Enfoque Simultaneo [L, R] (Tight Inferior y Superior) ────────────────
// string A, B; // Rellenar A con '0' a la izquierda hasta que sz(A) == sz(B)
// ll dp2[20][2][2][2]; // pos, tight_low, tight_high, leading_zero
// int min_d = tight_low  ? (A[pos] - '0') : 0;
// int max_d = tight_high ? (B[pos] - '0') : 9;
// for (int d = min_d; d <= max_d; ++d) {
//     bool n_low  = tight_low  && (d == min_d);
//     bool n_high = tight_high && (d == max_d);
//     bool n_lz   = lz && (d == 0);
//     ...
// }
