#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];
int distinct_count[MAXN];

// Usamos arreglo de sets. Evitamos punteros para prevenir Memory Leaks.
set<int> subtree_set[MAXN];

void dfs_small_to_large_set(int u, int p = -1)
{
    int largest_child = -1;
    int max_size = -1;

    // 1. Encontrar el hijo pesado
    for (int v : adj[u])
    {
        if (v != p)
        {
            dfs_small_to_large_set(v, u);
            if ((int)subtree_set[v].size() > max_size)
            {
                max_size = subtree_set[v].size();
                largest_child = v;
            }
        }
    }

    // 2. Heredar el set más grande en O(1)
    if (largest_child != -1)
    {
        swap(subtree_set[u], subtree_set[largest_child]);
    }

    // 3. Fusionar los hijos ligeros
    for (int v : adj[u])
    {
        if (v != p && v != largest_child)
        {
            // Inserción por rango: altamente optimizada en C++
            subtree_set[u].insert(subtree_set[v].begin(), subtree_set[v].end());

            // Liberar memoria del hijo procesado
            subtree_set[v].clear();
        }
    }

    // 4. Procesar el nodo actual
    subtree_set[u].insert(color[u]);

    // 5. Guardar la respuesta
    distinct_count[u] = subtree_set[u].size();
}