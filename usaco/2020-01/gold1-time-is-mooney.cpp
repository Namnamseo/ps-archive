#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = int(1e3) + 10;
const int inf = int(1e9);

int n, m, c;
int earn[maxn];
vector<int> e[maxn];

int _dp[2][maxn];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> c;
	for (int i=1; i<=n; ++i) cin >> earn[i];

	for (int i=1; i<=m; ++i) {
		int a, b;
		cin >> a >> b;
		e[a].push_back(b);
	}

	int ans = 0;
	int *dp = _dp[0], *tmp = _dp[1];

	fill(dp+1, dp+n+1, -inf);
	dp[1] = 0;
	for (int step=1; step<=1000; ++step) {
		fill(tmp+1, tmp+n+1, -inf);
		for (int i=1; i<=n; ++i) if (dp[i] > -inf) {
			for (int j:e[i]) {
				tmp[j] = max(tmp[j], dp[i]+earn[j]-c*(2*step-1));
			}
		}
		swap(dp, tmp);
		ans = max(ans, dp[1]);
	}

	cout << ans << '\n';

	return 0;
}
