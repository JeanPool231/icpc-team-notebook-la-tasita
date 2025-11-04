#include <bits/stdc++.h>
using namespace std;

#define ll long long
const double PI = acos(-1);

namespace FFT {
    static vector<int> rev;
    static vector<complex<double>> raices{{0,0},{1,0}};

    void fft(vector<complex<double>>& a, bool invertido) {
        int n = a.size();

        if (rev.size() != n) {
            int k = __builtin_ctz(n); // log2(n)
            rev.assign(n, 0);
            for (int i = 0; i < n; i++) {
                rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
            }
        }

        for (int i = 0; i < n; i++) {
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        if (raices.size() < n) {
            int k = __builtin_ctz(raices.size());
            raices.resize(n);
            while ((1 << k) < n) {
                double angulo = 2 * PI / (1 << (k + 1));
                for (int i = 1 << (k - 1); i < (1 << k); i++) {
                    raices[2 * i] = raices[i];
                    double ang = angulo * (2 * i + 1 - (1 << k));
                    raices[2 * i + 1] = complex<double>(cos(ang), sin(ang));
                }
                k++;
            }
        }

        for (int len = 1; len < n; len = len << 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    complex<double> u = a[i + j];
                    complex<double> v = a[i + j + len] * raices[len + j];
                    a[i + j] = u + v;
                    a[i + j + len] = u - v;
                }
            }
        }

        if (invertido) {
            reverse(a.begin() + 1, a.end());
            for (auto &x : a) x /= n;
        }
    }
} // namespace FFT

vector<ll> multiplicacion_polinomio(const vector<ll>& A, const vector<ll>& B) {
    int n1 = A.size(), n2 = B.size();
    if (n1 == 0 || n2 == 0) return vector<ll>();

    int n = 1;
    while (n < n1 + n2 - 1) n = n << 1;
    vector<complex<double>> fa(n), fb(n);
    for (int i = 0; i < n1; i++) fa[i] = complex<double>(A[i],0);
    for (int i = 0; i < n2; i++) fb[i] = complex<double>(B[i],0);

    FFT::fft(fa, false);
    FFT::fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    FFT::fft(fa, true);

    vector<ll> res(n1 + n2 - 1);
    for (int i = 0; i < res.size(); i++) {
        res[i] = llround(fa[i].real()); // Redondeo
    }
    return res;
}


int main() {
    vector<ll> A = {1, 2, 3}; // 1 + 2x + 3x^2
    vector<ll> B = {2, 0, 1}; // 2 + 0x + 1x^2
    vector<ll> C = multiplicacion_polinomio(A, B);
    return 0;
}
