#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define ios                      \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);

#define dbg(x) cerr << "[" << #x << "] = " << (x) << "\n"
#define dbgv(v)                  \
    cerr << "[" << #v << "] = "; \
    for (auto _x : (v))          \
        cerr << _x << " ";       \
    cerr << "\n"
#define dbgm(m)                \
    for (auto &_r : (m))       \
    {                          \
        for (auto _x : _r)     \
            cerr << _x << " "; \
        cerr << "\n";          \
    }

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define repr(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define each(x, a) for (auto &x : (a))

#define all(s) (s).begin(), (s).end()
#define rall(s) (s).rbegin(), (s).rend()
#define pb push_back
#define eb emplace_back
#define sz(v) ((int)((v).size()))

#define nl '\n'
#define ff first
#define ss second
#define yesi cout << "Yes\n"
#define nosi cout << "No\n"

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ld> vld;
typedef vector<ii> vii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<char> vc;

const ll LINF = (1LL << 62);

template <class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

int bit(int mask, int b) { return (mask >> b) & 1; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define randint(a, b) uniform_int_distribution<int>(a, b)(rng)

template <class T>
void read(T &x) { cin >> x; }
template <class F, class S>
void read(pair<F, S> &p) { cin >> p.first >> p.second; }
template <class T>
void read(vector<T> &v) { each(x, v) read(x); }

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