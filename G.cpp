#include<bits/stdc++.h>
using namespace std;

#define ll       long long
#define ull      unsigned ll
#define pii      pair<int, int>
#define pll      pair<ll, ll>
#define mp       make_pair
#define ff       first
#define ss       second
#define sz(x)    (int) x.size()
#define all(v)   v.begin(), v.end()

template <typename T> inline void smin(T &a, T b) {a = a < b ? a : b;}
template <typename T> inline void smax(T &a, T b) {a = a > b ? a : b;}

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl;}
template<typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ", ";
    err(++it, args...);
}

template <typename T> inline void Int(T &n) {
    n = 0; int f = 1; register int ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) n = (n << 3) + (n << 1) + ch - '0';
    n = n * f;
}

template <typename T, typename TT> inline void Int(T &n, TT &m) { Int(n); Int(m); }
template <typename T, typename TT, typename TTT> inline void Int(T &n, TT &m, TTT &l) { Int(n, m); Int(l); }

const int mod = (int) 1e9 + 7;

inline int add(int a, int b) {a += b; return a >= mod ? a - mod : a;}
inline int sub(int a, int b) {a -= b; return a < 0 ? a + mod : a;}
inline int mul(int a, int b) {return (ll) a * b % mod;}

const int inf = (int) 2e9 + 5;
const ll  Inf = (ll) 2e18 + 5;
const int N   = (int) 2e5 + 5;
const int Log = (int) 18;

std::vector<pii> g[N];
int par[Log][N], dep[N];
ll dp[N];

void lca_build(int u, int p = -1, int d = 0, ll dd = 0) {
	dep[u] = d; dp[u] = dd;
	for (int i = 1; i < Log; i++) {
		par[i][u] = par[i - 1][par[i - 1][u]];
	}
	for (auto xx : g[u]) {
		int v = xx.ff, w = xx.ss;
		if (p == v) continue;
		par[0][v] = u;
		lca_build(v, u, d + 1, dd + w);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = Log - 1; i >= 0; i--) {
		if (dep[par[i][u]] >= dep[v]) u = par[i][u];
	}
	if (u == v) return u;
	for (int i = Log - 1; i >= 0; i--) {
		if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
	}
	return par[0][u];
}

ll dis(int u, int v) {
	int l = lca(u, v);
	return dp[u] + dp[v] - 2 * dp[l];
}

int solve() {
    int n, q; Int(n, q);
    for(int i = 1; i < n; i++) {
    	int u, v, w; Int(u, v, w);
    	g[u].push_back({v, w});
    	g[v].push_back({u, w});
    }
    lca_build(1);
    while(q--) {
    	int n ; Int(n); n -= 2;
    	int a, b;
    	Int(a, b);
    	ll d = dis(a, b);
    	while(n--) {
            int x; Int(x);
            if(dis(x, a) > d and dis(x, a) > dis(x, b)) {
            	d = dis(x, a), b = x;
            }
            else if(dis(x, b) > d and dis(x, b) > dis(x, a)) {
            	d = dis(x, b), a = x;
            }
    	}
    	printf("%lld\n", d);
    }
    return 0;
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int test = 1, tc = 0;
    //Int(test);
    //cin >> test;
    while (test--) {
        //printf("Case %d: ", ++tc);
        solve();
    }
    return 0;
}
