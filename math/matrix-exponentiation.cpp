#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int MOD = 1e9+7;

struct Matrix {
  int n;
  vector<vector<ll>> mat;

  Matrix(int size) : n(size), mat(size, vector<ll>(size)) {}

  // Identity matrix
  static Matrix identity(int size) {
    Matrix I(size);
    for (int i = 0; i < size; i++)
      I.mat[i][i] = 1;
    return I;
  }

  // Matrix multiplication
  Matrix operator*(const Matrix& other) const {
    Matrix product(n);
    for (int i = 0; i < n; ++i)
      for (int k = 0; k < n; ++k)
        for (int j = 0; j < n; ++j) {
          product.mat[i][j] += mat[i][k] * other.mat[k][j];
          product.mat[i][j] %= MOD;
        }
    return product;
  }

  // Matrix exponentiation
  Matrix pow(ll power) const {
    Matrix result = identity(n);
    Matrix base = *this;

    while (power > 0) {
      if (power & 1)
        result = result * base;
      base = base * base;
      power >>= 1;
    }
    return result;
  }
};

ll fibonacci(int n) {
  if (n == 0) return 0;
  Matrix base(2);
  base.mat = {{1, 1}, {1, 0}};
  base = base.pow(n - 1);
  return base.mat[0][0]; // F(n)
}

int main() {
  for(int i = 0; i < 25; i++) 
    cout << fibonacci(i) << " ";
}


