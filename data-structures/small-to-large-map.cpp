#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int valores[MAXN];

// Estructura que guardará el estado (frecuencias, elementos únicos, etc.) para cada subárbol.
// Puede ser map<int,int>, set<int>, o una estructura personalizada.
map<int, int> subtree_map[MAXN];

void dfs_small_to_large(int u, int p = -1)
{
    int largest_child = -1;
    int max_size = -1;

    // PASO 1: Procesar hijos y encontrar el hijo "Pesado" (Heavy Child)
    for (int v : adj[u])
    {
        if (v != p)
        {
            dfs_small_to_large(v, u);
            // Identificamos el hijo cuya estructura de datos es la más grande
            if ((int)subtree_map[v].size() > max_size)
            {
                max_size = subtree_map[v].size();
                largest_child = v;
            }
        }
    }

    // PASO 2: Heredar el estado del hijo mayor en O(1)
    if (largest_child != -1)
    {
        // En tu código hacias: subtree[u] = subtree[largest]
        // std::swap hace exactamente lo mismo por debajo (intercambia punteros)
        swap(subtree_map[u], subtree_map[largest_child]);
    }

    // PASO 3: Mezclar los hijos "Ligeros" (Light Children)
    for (int v : adj[u])
    {
        if (v != p && v != largest_child)
        {
            // Iteramos sobre el hijo pequeño y lo insertamos en el grande (u)
            for (auto const &[val, count] : subtree_map[v])
            {
                // Aquí extraes o eliminas contribuciones previas si el problema lo requiere

                // Añadimos el valor al map del nodo actual
                subtree_map[u][val] += count;

                // Aquí calculas las nuevas contribuciones
            }
            // Opcional: Limpiar el map del hijo para liberar memoria
            subtree_map[v].clear();
        }
    }

    // PASO 4: Añadir el propio nodo actual (raíz de este subárbol)
    int mi_valor = valores[u];
    subtree_map[u][mi_valor]++;

    // PASO 5: Guardar la respuesta para el nodo u
    // res[u] = ...
}