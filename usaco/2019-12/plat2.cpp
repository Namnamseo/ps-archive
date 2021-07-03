#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

const int maxn = int(1e5) + 10;

int n, q;
vector<int> e[maxn];

int par[maxn];
int ti[maxn], to[maxn], rv[maxn];
int nt;

void dfs(int x) {
	rv[ti[x] = ++nt] = x;
	for(int y:e[x]) {
		if (y == par[x]) continue;
		par[y] = x;
		dfs(y);
	}
	to[x] = nt;
}

struct lazy {
	static const int M = 131072;
	ll t[M<<1];
	int len[M<<1];
	int lz[M<<1];

	void init(int l, int r, int p=1) {
		len[p] = r-l+1;
		if (l == r) return;
		int mid = (l+r)/2;
		init(l, mid, p*2);
		init(mid+1, r, p*2+1);
	}

	inline void acq(int x, int v) {
		t[x] += v * 1ll * len[x];
		lz[x] += v;
	}

	inline void flush(int x) {
		if (!lz[x]) return;
		rep(i, 2) acq(x*2+i, lz[x]);
		lz[x] = 0;
	}

	inline void pull(int p) {
		t[p] = t[p*2]+t[p*2+1];
	}

	void upd(int l, int r, int v, int p, int ml, int mr) {
		if (r < ml || mr < l) return;
		if (l <= ml && mr <= r) {
			acq(p, v); return;
		}
		flush(p);
		int mid = (ml+mr)/2;
		upd(l,r,v, p*2, ml, mid);
		upd(l,r,v, p*2+1, mid+1, mr);
		pull(p);
	}

	ll sum(int l, int r, int p, int ml, int mr) {
		if (r < ml || mr < l) return 0;
		if (l <= ml && mr <= r) return t[p];
		flush(p);
		int mid = (ml+mr)/2;
		return sum(l,r, p*2, ml, mid)+sum(l,r, p*2+1, mid+1, mr);
	}
};

lazy L;

int main()
{
	cppio();
	cin >> n >> q;
	rrep(i, n-1) {
		int a, b; cin >> a >> b;
		e[a].pb(b); e[b].pb(a);
	}
	dfs(1);

	L.init(1, n);
	static set<int> g[100010];
	for(;q--;) {
		int cmd; cin >> cmd;
		if (cmd == 1) {
			int v, c; cin >> v >> c;
			auto &s = g[c];
			{
				auto it = s.upper_bound(ti[v]);
				if (it != s.begin()) {
					--it;
					int u = rv[*it];
					if (to[v] <= to[u]) {
						continue;
					}
				}
			}
			auto il = s.lower_bound(ti[v]);
			auto ir = s.upper_bound(to[v]);
			for(auto it=il; it != ir; ++it) {
				int u = rv[*it];
				L.upd(ti[u], to[u], -1, 1, 1, n);
			}
			for(auto it=il; it != ir;) {
				it = s.erase(it);
			}
			L.upd(ti[v], to[v], +1, 1, 1, n);
			s.insert(ti[v]);
		} else {
			int v; cin >> v;
			cout << L.sum(ti[v], to[v], 1, 1, n) << '\n';
		}
	}
	return 0;
}
