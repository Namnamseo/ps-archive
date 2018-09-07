#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0; i<(n); ++i)
#define rrep(i,n) for(int i=1; i<=(n); ++i)

#define all(v) (v).begin(), (v).end()
#define x first
#define y second

#define pb push_back
#define eb emplace_back
using pp=pair<int,int>;

const int MAX_N = 200001;
const int MAX_V = 400001;

int n;

vector<int> gp[MAX_N];

struct asdf {
	int par[MAX_N];
	int tnode[MAX_N];

	vector<int> te[MAX_V];
	int tp[20][MAX_V];
	int tt[MAX_V];
	int v;

	void init(){
		iota(par+1, par+n+1, 1);
		iota(tnode+1, tnode+n+1, 1);
		v = n;
	}

	int root(int x){ return (x == par[x]) ? x : (par[x] = root(par[x])); }

	void connect(int x, int y, int tm){
		x = root(x); y = root(y);
		if(x == y) return;
		int a = tnode[x], b = tnode[y];
		tp[0][a] = tp[0][b] = ++v;
		tt[v] = tm;
		te[v].pb(a); te[v].pb(b);
		par[x] = y; tnode[y] = v;
	}

	int nt;
	int tin[MAX_V];
	int tout[MAX_V];

	void dfs(int x){
		tin[x] = nt + 1;
		if(x <= n) ++nt;
		for(int y:te[x]) dfs(y);
		tout[x] = nt;
	}

	void inflate(){
		rrep(i, 19) rrep(j, v) tp[i][j] = tp[i-1][tp[i-1][j]];
		dfs(v);
	}

	pp get_range(int v, int tb){
		for(int i=19; 0<=i; --i){
			int a = tp[i][v];
			if(!a) continue;
			if(tt[a] <= tb) v = a;
		}

		return {tin[v], tout[v]};
	}
} sl, sr;

struct seg2d {
	const static int M = 262144;
	vector<int> yv[M*2];

	void addp(int x, int y){
		for(x+=M; x; x>>=1) yv[x].pb(y);
	}

	void prepare(){
		for(auto& v:yv) sort(all(v));
	}

	inline bool exist(vector<int>& v, int d, int u){
		auto it = lower_bound(all(v), d);
		return (it != v.end()) && (*it <= u);
	}

	inline bool exist(int l, int r, int d, int u){
		for(l+=M, r+=M; l<=r; l>>=1, r>>=1){
			if(l%2==1){ if(exist(yv[l++], d, u)) return 1; }
			if(r%2==0){ if(exist(yv[r--], d, u)) return 1; }
		}
		return 0;
	}
} d2;

vector<int> check_validity(int N, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
	n = N;
	int m = X.size();
	rep(i, m){
		int x=X[i]+1, y=Y[i]+1;
		gp[x].pb(y); gp[y].pb(x);
	}

	sl.init();
	sr.init();

	for(int i=n; 1<=i; --i){
		for(int j:gp[i]) if(i<=j){
			sl.connect(i, j, n-i+1);
		}
	}

	rrep(i, n) for(int j:gp[i]) if(j<=i){
		sr.connect(i, j, i);
	}

	sl.inflate(); sr.inflate();
	rrep(i, n) d2.addp(sr.tin[i], sl.tin[i]);
	d2.prepare();

	int q = L.size();
	vector<int> ans(q);
	rep(i, q){
		pp xr = sr.get_range(E[i]+1, R[i]+1);
		pp yr = sl.get_range(S[i]+1, n-L[i]);
		ans[i] = d2.exist(xr.x, xr.y, yr.x, yr.y);
	}

	return ans;
}
