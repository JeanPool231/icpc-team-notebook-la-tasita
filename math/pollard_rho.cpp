#include <bits/stdc++.h>
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

// Multiplicacion modular para int128
u64 binpower(u64 base, u64 e, u64 mod)
{
    u64 result = 1;
    base %= mod;
    while (e)
    {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

// Test de primalidad de Miller Rabin
bool check(u64 n, u64 a, u64 d, int s)
{
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++)
    {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}
// Retorna true si es primo
bool MillerRabin(u64 n)
{
    if (n < 2)
        return false;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0)
    {
        d >>= 1;
        r++;
    }
    // Bases suficientes para verificar primalidad hasta 2^64
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n == a)
            return true;
        if (check(n, a, d, r))
            return false;
    }
    return true;
}

// Algoritmo Pollard Rho, devuelve un factor primo de n
u64 pollard_rho(u64 n)
{
    if (n % 2 == 0)
        return 2;
    if (MillerRabin(n))
        return n;

    u64 x = 2, y = 2, d = 1, c = 1;

    // Función pseudoaleatoria f(x) = x^2 + c
    auto f = [&](u64 x, u64 n, u64 c)
    {
        return ((u128)x * x + c) % n;
    };

    while (d == 1)
    {
        x = f(x, n, c);          // Tortuga (1 paso)
        y = f(f(y, n, c), n, c); // Liebre (2 pasos)

        u64 diff = x > y ? x - y : y - x;
        d = std::gcd(diff, n);

        if (d == n)
        {
            x = rand() % (n - 2) + 2;
            y = x;
            c = rand() % (n - 1) + 1;
            d = 1;
        }
    }
    return d;
}

// Función recursiva para obtener todos los factores primos y sus exponentes
void factorize(u64 n, map<u64, int> &factors)
{
    if (n == 1)
        return;
    if (MillerRabin(n))
    {
        factors[n]++;
        return;
    }
    u64 divisor = pollard_rho(n);
    factorize(divisor, factors);
    factorize(n / divisor, factors);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    u64 n;
    cin >> n;
    // factors, obtiene todos los factores y exponentes
    map<u64, int> factors;
    factorize(n, factors);
    return 0;
}