#include <algorithm>
#include <iostream>
#include <utility>
#include <tuple>
#define x first
#define y second
using namespace std;
using ll=long long;
const int maxn = int(1e6) + 10;
int n;
pair<int,int> d[maxn];
ll ans;
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i=1; i<=n; ++i) cin >> d[i].x;
	for (int i=1; i<=n; ++i) cin >> d[i].y;
	sort(d+1, d+n+1);
	for (int i=1; i<n; ++i) ans += (d[i+1].x-d[i].x) * 2ll * i * (n-i);
	sort(d+1, d+n+1, [&](const auto& a, const auto& b) { return a.y < b.y; });
	for (int i=1; i<n; ++i) ans += (d[i+1].y-d[i].y) * 2ll * i * (n-i);
	for (int i=1, x, y; tie(x, y)=d[i], i<=n; d[i]={x+y, x-y}, ++i);
	sort(d+1, d+n+1);
	for (int i=1; i<n; ++i) ans -= (d[i+1].x-d[i].x) * 1ll * i * (n-i);
	sort(d+1, d+n+1, [&](const auto& a, const auto& b) { return a.y < b.y; });
	for (int i=1; i<n; ++i) ans -= (d[i+1].y-d[i].y) * 1ll * i * (n-i);

	cout << ans << '\n';
	return 0;
}
