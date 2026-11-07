vi colores, distinct;
vll suma;
vii pares;
vector<vector<int>> graph;
map<pair<int, int>, ll> res;
map<int, int> original;
vector<map<int, int> *> subtree;

void dfs(int i, int parent = -1)
{
    int largest = -1;
    vector<int> children;

    for (int node : graph[i])
    {
        if (node != parent)
        {
            dfs(node, i);
            children.push_back(node);
            if (largest == -1 || subtree[largest]->size() < subtree[node]->size())
            {
                largest = node;
            }
        }
    }

    if (largest == -1)
    {
        subtree[i] = new map<int, int>();
        suma[i] = 0;
    }
    else
    {
        subtree[i] = subtree[largest];
        suma[i] = suma[largest];
    }

    for (int child : children)
    {
        if (child == largest)
            continue;

        for (const auto &[val, count] : *subtree[child])
        {
            int anterior = (*subtree[i])[val];
            ll quito = (ll)anterior * (ll)(original[val] - anterior);
            suma[i] -= quito;

            (*subtree[i])[val] += count;
            int nuevo = (*subtree[i])[val];
            ll anado = (ll)nuevo * (ll)(original[val] - nuevo);
            suma[i] += anado;
        }
    }

    int col = colores[i];
    int anterior = (*subtree[i])[col];
    ll quito = (ll)anterior * (ll)(original[col] - anterior);
    suma[i] -= quito;

    (*subtree[i])[col] += 1;
    int nuevo = (*subtree[i])[col];
    ll anado = (ll)nuevo * (ll)(original[col] - nuevo);
    suma[i] += anado;

    distinct[i] = subtree[i]->size();

    if (parent != -1)
    {
        res[{parent, i}] = suma[i];
        res[{i, parent}] = suma[i];
    }
}

void solve()
{
    int n;
    cin >> n;
    colores.resize(n);
    distinct.assign(n, 0);
    read(colores);
    original.clear();
    each(color, colores)
    {
        original[color]++;
    }
    suma.assign(n, 0);
    pares.resize(n - 1);
    graph.assign(n, vector<int>());
    subtree.assign(n, nullptr);
    res.clear();

    rep(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        pares[i] = {u, v};
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(0);
    for (int i = 0; i < n - 1; i++)
    {
        cout << res[pares[i]];
        if (i < n - 2)
            cout << " ";
    }
    cout << nl;
}

int main()
{
    ios int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
