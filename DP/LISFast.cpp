// LIS Fast O(N log N)
int LISFast(const vi& arr) {
    vi res;
    each(x, arr) {
        auto it = lower_bound(all(res), x); // upper_bound para no estrictamente creciente
        if (it == res.end()) res.pb(x);
        else *it = x;
    }
    return sz(res);
}

// LIS Fast con Reconstrucción - O(N log N)
vi LISFastReconstruccion(const vi& arr) {
    int n = sz(arr);
    vi res, resIndex, padre(n, -1);

    rep(i, n) {
        int x = arr[i];
        auto it = lower_bound(all(res), x);
        int pos = it - res.begin();

        if (it == res.end()) {
            res.pb(x);
            resIndex.pb(i);
        } else {
            *it = x;
            resIndex[pos] = i;
        }

        if (pos > 0) padre[i] = resIndex[pos - 1];
    }

    vi lis;
    int idx = resIndex.back();
    while (idx != -1) {
        lis.pb(arr[idx]);
        idx = padre[idx];
    }
    reverse(all(lis));
    return lis;
}

