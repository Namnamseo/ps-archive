#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define pb push_back

const int maxn = int(2e5) + 10;

int n, m;
vector<int> te[maxn];

int par[20][maxn];
int dep[maxn];
void dfs(int x) {
	for(int y:te[x]) if (par[0][x] != y) {
		dep[y] = dep[x]+1;
		par[0][y] = x;
		dfs(y);
	}
}

int lca(int a, int b) {
	if (dep[a] > dep[b]) swap(a, b);
	for(int i=19, df=dep[b]-dep[a]; i>=0; --i) {
		if (1&(df>>i)) b = par[i][b];
	}
	if (a == b) return a;
	for(int i=19; i>=0; --i)
		if (par[i][a] != par[i][b])
			a = par[i][a], b = par[i][b];
	return par[0][a];
}

int dp[maxn];

ll ans;

void d2(int x) {
	ll cs = 0;
	for(int y:te[x]) if (par[0][y] == x) {
		d2(y);
		dp[x] += dp[y];
		ll t = dp[y];
		cs += t * (t-1) / 2;
	}
	ll c = dp[x];
	if (x != 1) {
		ans += c * (c-1) / 2 - cs;
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for(int i=1; i<n; ++i){
		int a,b; cin >> a >> b;
		te[a].pb(b); te[b].pb(a);
	}

	dfs(1);
	for(int i=1; i<20; ++i) {
		for(int j=1; j<=n; ++j)
			par[i][j] = par[i-1][par[i-1][j]];
	}

	for(int i=n; i<=m; ++i){
		int a,b; cin >> a >> b;
		int l = lca(a, b);
		++dp[a]; ++dp[b]; dp[l]-=2;
	}

	d2(1);
	
	cout << ans << endl;
	return 0;
}
