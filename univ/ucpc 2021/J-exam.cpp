#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
using ll=long long;
const ll inf = 1ll<<60;

int n;
int arr[22][22];

ll Count(ll k) {
	ll walk_ans;
	auto Walk = [&](int x, int y, int dx, int dy, int msk, int steps) {
		walk_ans = inf;
		ll ans=-inf, s=0, mn=0;
		for (int i=0;; ++i) {
			s += arr[x][y];
			ans = max(ans, s-mn);
			if (i == steps) break;
			mn = min(mn, s);
			if (1&(msk>>i)) x+=dy, y+=dx;
			else x+=dx, y+=dy;
		}
		if (ans <= k) walk_ans = s-mn;
	};

	ll ret = 0;
	for (int x=1, y=n; y; ++x, --y) {
		static ll va[1<<20], vb[1<<20];
		int ca=0, cb=0;

		{ const int am = (1<<(n-1))-1, pc = x-1;
		for (int m=0; m<=am; ++m) if (__builtin_popcount(m) == pc) {
			Walk(1, 1, 0, 1, m, n-1);
			if (walk_ans != inf) va[ca++] = walk_ans;
		} }

		for (int nxt=0; nxt<2; ++nxt) if (x+nxt <= n && y+(1-nxt) <= n) {
		const int am = (1<<(n-2))-1, pc = n-(x+nxt);
		for (int m=0; m<=am; ++m) if (__builtin_popcount(m) == pc) {
			Walk(n, n, 0, -1, m, n-2);
			if (walk_ans != inf) vb[cb++] = walk_ans;
		} }

		sort(va, va+ca);
		sort(vb, vb+cb);
		int ob=cb;
		for (int i=0; i<ca; ++i) {
			while (ob && va[i]+vb[ob-1]>k) --ob;
			ret += ob;
		}
	}

	return ret;
}

int main() { cin.tie(0)->sync_with_stdio(0);
	ll k;
	cin >> n >> k;
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) cin >> arr[i][j];
	if (n == 1) {
		cout << (k == arr[1][1]) << '\n';
		return 0;
	}
	cout << (Count(k) - Count(k-1)) << '\n';
	return 0;
}
