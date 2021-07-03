#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
using pp=pair<int, int>;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)

const int maxn = int(1e5) + 10;

int n;
ll ans;
int c[maxn][2];

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;
	rrep(i, 2*n) {
		int x, y; cin >> x >> y;
		auto Bound = [&](int &v, int l, int r) {
			if (v < l) { ans += l-v; v = l; }
			else if (v > r) { ans += v-r; v = r; }
		};
		Bound(x, 1, n);
		Bound(y, 1, 2);
		++c[x][y-1];
	}

	int du = 0, dd = 0;
	for (int i=1; i<=n; ++i) {
		du += c[i][0]; dd += c[i][1];
		int amt = 0;
		if (du > i && dd < i) amt = min(du - i, i - dd);
		else if (du < i && dd > i) amt = max(du - i, i - dd);
		du -= amt; dd += amt; ans += abs(amt);
		ans += abs(du-i) + abs(dd-i);
	}

	cout << ans << '\n';

	return 0;
}
