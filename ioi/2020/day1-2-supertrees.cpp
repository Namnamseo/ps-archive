#include "supertrees.h"
#include <vector>
#include <numeric>
using namespace std;
#define rep(i, n) for(int i=0; i<n; ++i)
#define pb push_back

int n;

namespace unf {
	int par[1010];
	void init() {
		iota(par, par+n, 0);
	}
	int r(int x) { return (x==par[x]) ? x : (par[x]=r(par[x])); }
	void join(int a, int b) {
		a = r(a); b = r(b);
		if (a == b) return;
		par[a] = b;
	}
	bool same(int a, int b) { return r(a) == r(b); }
};
using namespace unf;

vector<int> g[1010];

int ans[1010][1010];
vector<int> go[1010];
int work(int gi, auto &p) {
	auto &v = g[gi];

	if (v.size() == 1u) return 1;

	for(int x:v) par[x] = x;
	vector<int> v1;
	for(int x:v) {
		bool ok = 0;
		for(int y:v) if (p[x][y] == 1 && x != y) join(x, y), ok = 1;
		if (ok) v1.pb(x);
	}

	for(int x:v1) go[r(x)].pb(x);
	for(int x:v1) if (par[x] == x) {
		auto &t = go[x];
		int gs = t.size();
		for(int i=0; i+1<gs; ++i) {
			ans[t[i]][t[i+1]] = 1;
			ans[t[i+1]][t[i]] = 1;
		}
		for(int a:t) for(int b:t) if (p[a][b] != 1) return 0;
	}

	for(int x:v) for(int y:v) {
		if ((r(x)==r(y)) != (p[x][y] == 1)) return 0;
	}

	vector<int> cyc;
	for(int x:v) if (par[x] == x) cyc.pb(x);
	for(int i=0, s=cyc.size(); i<s-1; ++i) ans[cyc[i]][cyc[i+1]] = ans[cyc[i+1]][cyc[i]] = 1;
	if (cyc.size() == 2u) return 0;
	if (cyc.size() >= 2u) ans[cyc[0]][cyc.back()] = ans[cyc.back()][cyc[0]] = 1;

	return 1;
}

int construct(vector<vector<int>> p) {
	n = p.size();

	unf::init();

	rep(i, n) rep(j, n) if (p[i][j]) { if (p[i][j] == 3) return 0; join(i, j); }
	rep(i, n) rep(j, n) if (same(i, j) != !!p[i][j]) return 0;

	rep(i, n) g[r(i)].pb(i);

	rep(i, n) if (par[i] == i) if (!work(i, p)) return 0;

	rep(i, n) rep(j, n) p[i][j] = ans[i][j];
	build(p);

	return 1;
}
