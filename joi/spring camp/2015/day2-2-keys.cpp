#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
using pp=pair<int,int>;
const int maxn = int(2e3) + 10;
#define pb push_back

int n, m, k;
pp d[maxn];

int tm[maxn*2], tn;
int user[maxn*2][2];

int F(int t) { return lower_bound(tm, tm+tn, t) - tm; }

bool vis[maxn];

int dp[2010][2010][2];
int Solve(int n, int k, vector<int> vv, vector<int> ve)
{
	const int inf = int(1e9);
	for (int j=0; j<=k; ++j) dp[0][j][0] = dp[0][j][1] = inf;

	dp[0][0][0] = 0; dp[0][1][1] = vv[0];

	for (int i=1; i<n; ++i) {
		for (int j=0; j<=k; ++j) {
			dp[i][j][0] = inf;
			for (int t=0; t<2; ++t) {
				dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][t]);
			}

			dp[i][j][1] = inf;

			if (j >= 1) {
				if (dp[i-1][j-1][0] != inf) {
					dp[i][j][1] = min(dp[i][j][1], dp[i-1][j-1][0] + vv[i]);
				}
				if (dp[i-1][j-1][1] != inf) {
					dp[i][j][1] = min(dp[i][j][1], dp[i-1][j-1][1] + vv[i] - ve[i]);
				}
			}
		}
	}

	return min(dp[n-1][k][0], dp[n-1][k][1]);
}

int main()
{
	cin >> n >> m >> k;
	for (int i=1; i<=n; ++i) {
		int s, t; cin >> s >> t;
		d[i] = {s, t};
		tm[tn++] = s;
		tm[tn++] = t;
	}
	tm[tn++] = 0;
	tm[tn++] = m;
	sort(tm, tm+tn);

	sort(d+1, d+n+1);
	for (int i=1; i<=n; ++i) {
		auto [s, t] = d[i];
		s = F(s); t = F(t)-1;
		d[i] = {s, t};
		user[s][0] = i;
		user[t][1] = i;
	}

	vector<int> vv, ve;
	for (int i=1; i<=n; ++i) if (!vis[i]) {
		vis[i] = 1;
		{ auto [s, t] = d[i];
		if (s == t) {
			vv.pb(tm[t+1]-tm[s]); ve.pb(0);
			continue;
		} }

		{ auto [s, t] = d[i]; vv.pb(tm[t+1]-tm[t] + tm[s+1]-tm[s]); ve.pb(0); }
		int ci = i;
		while (true) {
			auto [s, t] = d[ci];

			int ni = user[t][0];
			if (!ni) break;
			vis[ni] = true;
			auto [ns, nt] = d[ni];
			vv.pb(tm[nt+1]-tm[nt] + tm[ns+1]-tm[ns]); ve.pb(tm[t+1]-tm[t]);
			ci = ni;
		}
	}

	int ans = m - Solve(n, n-k, vv, ve);

	cout << ans << '\n';

	return 0;
}
