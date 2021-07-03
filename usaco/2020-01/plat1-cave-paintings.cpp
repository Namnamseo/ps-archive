#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std; using pp=pair<int,int>; using ll=long long;
#define x first
#define y second

int n, m;
char s[1010][1010];

vector<pp> g[1010];
ll dp[1010][1010];
int gi[1010][1010];
int gc[1010];

int par[2010];
int root(int x) { return x == par[x] ? x : par[x] = root(par[x]); }
void join(int a, int b) { par[root(a)] = root(b); }

const int mod = int(1e9) + 7;

bool touch(pp a, pp b) {
	return max(a.x, b.x) <= min(a.y, b.y);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m;
	for (int i=1; i<=n; ++i) cin >> (s[i]+1);

	for (int i=2; i<n; ++i) {
		for (int j=1; j<=m;) {
			if (s[i][j] == '#') { ++j; continue; }
			int k = j;
			while (k+1 <= m && s[i][k+1] == '.') ++k;
			g[i].emplace_back(j, k);
			j = k+1;
		}
	}

	ll ans = 1;
for (int r=n-1; 1<=r; --r) {
	auto &vu = g[r], &vd = g[r+1];
	int su = vu.size(), sd = vd.size();

	static vector<int> adj[1010];

	for (int i=0, di=0; i<su; ++i) {
		adj[i].clear();
		while (di<sd && vd[di].y < vu[i].x) ++di;
		while (di<sd && touch(vd[di], vu[i])) {
			adj[i].push_back(di++);
		}
		if (!adj[i].empty()) di = adj[i].back();
	}

	iota(par, par+sd+su, 0);

	static int gn[2010], gnn;
	const int gnd = gc[r+1];
	fill(gn, gn+gnd+su, -1); gnn = 0;

	for (int i=0; i<su; ++i) for (int j:adj[i]) join(gi[r+1][j], gnd+i);
	for (int i=0; i<su; ++i) {
		int t = root(gnd+i);
		if (gn[t] == -1) gn[t] = gnn++;
		gi[r][i] = gn[t];
	}
	gc[r] = gnn;

	for (int i=0; i<gnn; ++i) dp[r][i] = 1;

	for (int i=0; i<gnd; ++i) {
		int t = root(i);
		if (gn[t] == -1) {
			(ans *= dp[r+1][i]) %= mod;
		} else {
			int gg = gn[t];
			(dp[r][gg] *= dp[r+1][i]) %= mod;
		}
	}

	for (int i=0; i<gnn; ++i) if (++dp[r][i] == mod) dp[r][i] = 0;
}

	cout << ans << '\n';

	return 0;
}
