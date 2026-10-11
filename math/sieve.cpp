// Sieve of Eratosthenes - O(N log log N)

// ─── 1. Criba Estandar (Arreglo Booleano) ────────────────────────────────────
const int MAXN = 1e6 + 5;
bool is_prime[MAXN];
vi primes;

void sieve() {
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;

    // Tachar pares primero
    for (int i = 4; i < MAXN; i += 2) is_prime[i] = false;

    // Solo revisar impares
    for (int i = 3; (ll)i * i < MAXN; i += 2) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j < MAXN; j += 2 * i) {
            is_prime[j] = false;
        }
    }

    primes.pb(2);
    for (int i = 3; i < MAXN; i += 2) {
        if (is_prime[i]) primes.pb(i);
    }
}

// ─── 2. Criba con Bitset (Ultra Rapida, 8x menos memoria, N hasta 1e7) ──────
const int MAX_BITSET = 10000005;
bitset<MAX_BITSET> bs;
vi primes_bs;

void bitsetSieve() {
    bs.set(); // Pone todos los bits en 1
    bs[0] = bs[1] = 0;
    for (int i = 4; i < MAX_BITSET; i += 2) bs[i] = 0;

    for (int i = 3; (ll)i * i < MAX_BITSET; i += 2) {
        if (bs[i]) {
            for (int j = i * i; j < MAX_BITSET; j += 2 * i) {
                bs[j] = 0;
            }
        }
    }

    primes_bs.pb(2);
    for (int i = 3; i < MAX_BITSET; i += 2) {
        if (bs[i]) primes_bs.pb(i);
    }
}
