#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Funcion para canonizar un vector e inclinarlos a un lado
// Ejemplo: (-12, 3) -> (4, -1)

pair<ll, ll> canon(pair<ll, ll> a)
{
    ll div = gcd(a.first, a.second);
    a.first /= div;
    a.second /= div;
    if (a.first < 0 || (a.first == 0 && a.second < 0))
    {
        a.first *= -1;
        a.second *= -1;
    }
    return {a.first, a.second};
}

// Funcion para obtener el vector perpendicular de un vector

pair<ll, ll> perp(pair<ll, ll> v)
{
    return canon({-v.second, v.first});
}