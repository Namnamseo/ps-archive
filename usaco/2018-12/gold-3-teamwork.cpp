#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
int n, k;
int a[10010];
ll dp[10010];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> k;

	for (int i=1; i<=n; ++i) {
		cin >> a[i];
		int cm = 0;
		for (int j=i; i-k+1<=j && 1<=j; --j) {
			cm = max(cm, a[j]);
			dp[i] = max(dp[i], dp[j-1] + (i-j+1)*1ll*cm);
		}
	}

	cout << dp[n] << '\n';

	return 0;
}
