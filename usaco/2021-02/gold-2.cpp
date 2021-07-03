#include <iostream>
#include <vector>
using namespace std;

int n;
int a[310];

int dp[310][310];
const int inf = 1e9;

vector<int> pc[310];

int main() {
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;
	for (int i=1; i<=n; ++i) cin >> a[i];

	for (int i=1; i<=n; ++i) dp[i][i] = 1;
	for (int len=2; len<=n; ++len) for (int l=1, r; (r=l+len-1)<=n; ++l) {
		dp[l][r] = 1 + min(dp[l+1][r], dp[l][r-1]);
		if (a[l] == a[r]) {
			dp[l][r] = min(dp[l][r], 1 + dp[l+1][r-1]);
		}
		for (int i=l+1; i<r; ++i) {
			if (a[l] == a[i]) {
				dp[l][r] = min(dp[l][r],
					dp[l+1][i-1] + dp[i][r]);
			}
			if (a[i] == a[r]) {
				dp[l][r] = min(dp[l][r],
					dp[l][i] + dp[i+1][r-1]);
			}
		}
	}

	cout << dp[1][n] << '\n';

	return 0;
}
