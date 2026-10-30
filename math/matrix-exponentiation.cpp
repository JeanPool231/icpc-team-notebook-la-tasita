#include <bits/stdc++.h>

using namespace std;

#define ll long long
const ll MOD = 998244353;

struct Matrix
{
  int rows, cols;
  vector<vector<ll>> mat;

  // Matriz rectangular
  Matrix(int r, int c) : rows(r), cols(c), mat(r, vector<ll>(c, 0)) {}

  // Matriz cuadrada
  Matrix(int n) : rows(n), cols(n), mat(n, vector<ll>(n, 0)) {}

  // Identity matrix (matriz cuadrada)
  static Matrix identity(int n)
  {
    Matrix I(n);
    for (int i = 0; i < n; i++)
      I.mat[i][i] = 1;
    return I;
  }

  // Matrix multiplication (permite matrices rectangulares)
  Matrix operator*(const Matrix &other) const
  {
    Matrix product(rows, other.cols);
    for (int i = 0; i < rows; ++i)
      for (int k = 0; k < cols; ++k)
      {
        ll val = mat[i][k] % MOD;
        for (int j = 0; j < other.cols; ++j)
        {
          product.mat[i][j] = (product.mat[i][j] + val * other.mat[k][j]) % MOD;
        }
      }
    return product;
  }

  // Matrix exponentiation (solo matrices cuadradas rows == cols)
  Matrix pow(ll power) const
  {
    Matrix result = identity(rows);
    Matrix base = *this;

    while (power > 0)
    {
      if (power & 1)
        result = result * base;
      base = base * base;
      power >>= 1;
    }
    return result;
  }
};

ll fibonacci(int n)
{
  if (n == 0)
    return 0;
  Matrix base(2);
  base.mat = {{1, 1}, {1, 0}};
  base = base.pow(n - 1);
  return base.mat[0][0]; // F(n)
}

// Ejemplo de uso anterior (comentado para pegar el algoritmo con la plantilla):
// int main() {
//   for(int i = 0; i < 25; i++)
//     cout << fibonacci(i) << " ";
// }

// Para crear Funciones con Recurrencias de la forma: F(n) = a1*F(n-1) + a2*F(n-2) + ... + ad*F(n-d)
// La matriz inicial es: A = {{F(1), F(2), ... , F(d)}}
/* La matriz clave es:
   B =
   {
   {0 , 0 , 0, ... , ad},
   {1 , 0 , 0, ... , ad-1},
   {0 , 1 , 0, ... , ad-2},
   {. , . , ., ... , a2},
   {0 , 0 , 0,  1  , a1}
   }

   Se realiza:
   B = B.pow(n-d);
   A = A * B;

   En A queda: A = {{F(n-(d-1)), F(n-(d-2)), ..., F(n)}}
   Entonces F(n) = A[0][d-1];
*/
