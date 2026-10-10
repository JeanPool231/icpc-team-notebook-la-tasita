// Subset Sum con Bitset & Binary Splitting - O((S / 64) * sum(log count))
// 1. Bitset acelera transiciones booleanas dividiendo entre 64.
// 2. Binary splitting agrupa elementos repetidos: si 'val' aparece C veces,
//    se descompone en potencias de 2: 1*val, 2*val, 4*val, ..., R*val.

const int MAX_SUM = 500005;

// ─── 1. Bounded Subset Sum con Bitset Estandar ──────────────────────────────
bitset<MAX_SUM> subsetSum(const vi& arr, int target) {
    // 1. Contar frecuencias
    map<int, int> freq;
    each(x, arr) if (x <= target) freq[x]++;

    // 2. Descomposicion binaria de frecuencias
    vi items;
    for (auto& [val, count] : freq) {
        int c = min(count, target / val);
        for (int k = 1; k <= c; k *= 2) {
            items.pb(val * k);
            c -= k;
        }
        if (c > 0) items.pb(val * c);
    }

    // 3. DP con Bitset
    bitset<MAX_SUM> dp;
    dp[0] = 1;
    each(w, items) {
        dp |= (dp << w);
    }
    return dp;
}

// ─── 2. Bitset con Tamaño Dinamico (Template Recursivo) ─────────────────────
// Ejecuta con bitset<len> ajustado al target para no desperdiciar operaciones
int reachable_max = 0;
template <int len = 1>
void dynamicSubsetSum(int target, const vi& items) {
    if (target >= len) {
        dynamicSubsetSum<min(len * 2, MAX_SUM)>(target, items);
        return;
    }
    bitset<len> dp;
    dp[0] = 1;
    each(x, items) dp |= (dp << x);

    for (int i = target; i >= 0; --i) {
        if (dp[i]) {
            reachable_max = i;
            break;
        }
    }
}

// Ejemplo de uso: maxima suma posible <= target con binary splitting
int getMaxSubsetSum(const vi& valores, int target) {
    map<int, int> freq;
    each(x, valores) if (x <= target) freq[x]++;
    vi items;
    for (auto& [val, count] : freq) {
        int c = min(count, target / val);
        for (int k = 1; k <= c; k *= 2) {
            items.pb(val * k);
            c -= k;
        }
        if (c > 0) items.pb(val * c);
    }
    reachable_max = 0;
    dynamicSubsetSum(target, items);
    return reachable_max;
}


// ─── 3. Reconstruccion de Elementos Tomados ─────────────────────────────────
vi reconstructSubsetSum(const vi& arr, int target) {
    int n = sz(arr);
    // Para reconstruccion exacta se pueden guardar bitsets por capas o usar backtrack
    vector<bitset<MAX_SUM>> dp(n + 1);
    dp[0][0] = 1;
    rep(i, n) {
        dp[i + 1] = dp[i] | (dp[i] << arr[i]);
    }
    if (!dp[n][target]) return {}; // Imposible

    vi taken;
    int cur = target;
    for (int i = n - 1; i >= 0; --i) {
        if (cur >= arr[i] && dp[i][cur - arr[i]]) {
            taken.pb(arr[i]);
            cur -= arr[i];
        }
    }
    return taken;
}
