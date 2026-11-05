#include <bits/stdc++.h>
using namespace std;

// Funcion para canonizar un vector e inclinarlos a un lado
// Ejemplo: (-12, 3) -> (4, -1)

pair<int, int> canon(pair<int, int> a)
{
    int div = gcd(a.first, a.second);
    a.first /= div;
    a.second /= div;
    if (a.first < 0 || (a.first == 0 && a.second < 0))
    {
        a.first *= -1;
        a.second *= -1;
    }
    return a;
}