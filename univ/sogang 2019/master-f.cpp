#include <iostream>
#include <cstring>
using namespace std;
using ll=long long;

ll dp[10][100001];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int tc; cin >> tc;
for(;tc--;) {
	int n, m; cin >> n >> m;

	for (int i=0; i<=n; ++i) {
		memset(dp[i], -1, sizeof(ll)*m);
	}
	dp[0][0] = 0;
	for (int i=1; i<=n; ++i) {
		for (int j=0; j<m; ++j) if (dp[i-1][j] != -1) {
			for (int d=0; d<10; ++d) {
				ll v = dp[i-1][j] * 10 + d;
				int vm = (j*10+d)%m;
				dp[i][vm] = max(dp[i][vm], v);
			}
			{
				ll v = dp[i-1][j] * 100 + 11;
				int vm = (j*100+11)%m;
				dp[i][vm] = max(dp[i][vm], v);
			}
		}
	}

	cout << dp[n][0] << '\n';
}
	return 0;
}
