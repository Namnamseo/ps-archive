#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;
int g, n;
const int maxn = int(1e5) + 10;

struct {
	int sx, sy;
	int tx, ty;
	int len() {
		return abs(tx-sx) + abs(ty-sy);
	}
} d[maxn];
int dp[maxn];

int xv[2*maxn+10], xn;

int os[maxn];
int ot[maxn];

const int M = 262144;
int tree[M<<1];

void upd(int p, int v) {
	p = lower_bound(xv, xv+xn, p) - xv;
	for (p+=M; p; p/=2) {
		tree[p] = max(tree[p], v);
	}
}

int qry(int l, int r) {
	l = lower_bound(xv, xv+xn, l) - xv;
	r = lower_bound(xv, xv+xn, r) - xv;
	int ret = 0;
	for(l+=M, r+=M; l<=r; l/=2, r/=2) {
		if (l%2 == 1) ret = max(ret, tree[l++]);
		if (r%2 == 0) ret = max(ret, tree[r--]);
	}

	return ret;
}

int main()
{
	cin >> g >> n;
	for (int i=1; i<=n; ++i) {
		int sx, sy, tx, ty;
		cin >> sx >> sy >> tx >> ty;
		if (sx < 0 || sy < 0 || tx > g || ty > g) {
			--i; --n; continue;
		}
		d[i] = {sx, sy, tx, ty};
		xv[xn++] = sx;
		xv[xn++] = tx;
	}
	xv[xn++] = 0;
	xv[xn++] = g;
	sort(xv, xv+xn);

	iota(os+1, os+n+1, 1); iota(ot+1, ot+n+1, 1);
	sort(os+1, os+n+1, [&](const int& a, const int& b) {
		return make_pair(d[a].sy, d[a].sx) <
			   make_pair(d[b].sy, d[b].sx);
	});
	sort(ot+1, ot+n+1, [&](const int& a, const int& b) {
		return d[a].ty < d[b].ty;
	});

	int ti = 1;
	for (int _i=1; _i<=n; ++_i) {
		int i = os[_i];
		while (ti<=n) {
			int j = ot[ti];
			if (d[j].ty > d[i].sy) break;
			upd(d[j].tx, dp[j]);
			++ti;
		}

		dp[i] = qry(0, d[i].sx) + d[i].len();
		if (d[i].sy == d[i].ty) {
			upd(d[i].tx, dp[i]);
		}
	}

	while (ti<=n) {
		int j = ot[ti++];
		upd(d[j].tx, dp[j]);
	}

	cout << ((2*g) - qry(0, g)) << '\n';

	return 0;
}
