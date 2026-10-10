#include <bits/stdc++.h>
using namespace std;

// ─── Fast IO ────────────────────────────────────────────────────────────────
#define ios ios::sync_with_stdio(false); cin.tie(nullptr);

// ─── Debug (solo activo en LOCAL, se elimina en juicio) ─────────────────────
#ifdef LOCAL
  #define dbg(x)  cerr << "[" << #x << "] = " << (x) << "\n"
  #define dbgv(v) cerr << "[" << #v << "] = "; for(auto _x:(v)) cerr<<_x<<" "; cerr<<"\n"
  #define dbgm(m) for(auto& _r:(m)){for(auto _x:_r)cerr<<_x<<" ";cerr<<"\n";}
#else
  #define dbg(x)
  #define dbgv(v)
  #define dbgm(m)
#endif

// ─── Macros de iteración ────────────────────────────────────────────────────
#define rep(i,n)    for(int i=0;i<(int)(n);i++)
#define rep1(i,n)   for(int i=1;i<=(int)(n);i++)
#define repr(i,n)   for(int i=(int)(n)-1;i>=0;i--)
#define each(x,a)   for(auto& x:(a))

// ─── Macros de contenedor ───────────────────────────────────────────────────
#define all(s)   (s).begin(),(s).end()
#define rall(s)  (s).rbegin(),(s).rend()
#define pb       push_back
#define eb       emplace_back
#define sz(v)    ((int)((v).size()))

// ─── Shortcuts ──────────────────────────────────────────────────────────────
#define nl       '\n'
#define ff       first
#define ss       second
#define yesi     cout<<"Yes\n"
#define nosi     cout<<"No\n"

// ─── Typedefs ────────────────────────────────────────────────────────────────
typedef long long      ll;
typedef long double    ld;
typedef pair<int,int>  ii;
typedef pair<ll,ll>    pll;
typedef vector<int>    vi;
typedef vector<ll>     vll;
typedef vector<ld>     vld;
typedef vector<ii>     vii;
typedef vector<pll>    vpll;
typedef vector<vi>     vvi;
typedef vector<vll>    vvll;
typedef vector<string> vs;
typedef vector<char>   vc;

// ─── Constantes ─────────────────────────────────────────────────────────────
const ll LINF = (1LL << 62);

// ─── ckmin / ckmax ──────────────────────────────────────────────────────────
template<class T> bool ckmin(T& a, const T& b){ return b<a ? a=b,1:0; }
template<class T> bool ckmax(T& a, const T& b){ return b>a ? a=b,1:0; }

// ─── Bit helper ─────────────────────────────────────────────────────────────
int bit(int mask, int b){ return (mask >> b) & 1; }

// ─── RNG ────────────────────────────────────────────────────────────────────
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define randint(a,b) uniform_int_distribution<int>(a,b)(rng)

// ─── Lectura rápida genérica ─────────────────────────────────────────────────
template<class T>            void read(T& x)            { cin >> x; }
template<class F, class S>   void read(pair<F,S>& p)    { cin >> p.first >> p.second; }
template<class T>            void read(vector<T>& v)    { each(x,v) read(x); }

// ────────────────────────────────────────────────────────────────────────────

void solve() {
  
}

int main(){
    ios
    int t = 1;
    // cin >> t;
    while(t--){
      solve();
    }
    return 0;
}
