#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
using pli=pair<ll,int>;
const int maxn = int(5e5) + 10;
const ll inf = 1ll<<60;

int n;
pli d[maxn];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;
	for (int i=1; i<=n; ++i) cin >> d[i].first >> d[i].second;
	sort(d+1, d+n+1);

	ll cp=0, pm=-inf, ans=-inf;
	for (int i=1; i<=n; ++i) {
		cp += d[i].second;
		ans = max(ans, cp + pm - d[i].first);
		ans = max(ans, ll(d[i].second));
		pm = max(pm, d[i].first - (cp - d[i].second));
	}

	cout << ans << '\n';

	return 0;
}
