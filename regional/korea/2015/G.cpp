#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <cmath>
#define x first
#define y second
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
using namespace std;
using pp=pair<int, int>;
using ll=long long;
const int maxn = int(1e5) + 10;

int n, q;
pp d[maxn];
pp w[maxn];
double ans[maxn];

bool ccw(pp a, pp b, pp c) {
	return (c.y-a.y)*1ll*(b.x-a.x) > (c.x-a.x)*1ll*(b.y-a.y);
}

pp Qp(int i) {
	int ei = w[i].x, ej = (ei+1);
	ll r = w[i].y;
	int ed = (abs(d[ei].x-d[ej].x) + abs(d[ei].y-d[ej].y));
	return {
		(d[ei].x * (ed-r) + d[ej].x * r) / ed,
		(d[ei].y * (ed-r) + d[ej].y * r) / ed
	};
}

void Work() {
	cin >> n;
	rep(i, n) cin >> d[i].x >> d[i].y;
	cin >> q;
	rep(i, q) cin >> w[i].x >> w[i].y;

	d[n] = d[0];
	sort(w, w+q);

	static pp h[maxn];
	int hs = 1; h[0] = d[0];
	int nq = q-1;
	double ds = 0, ans = 0;

	auto Hd = [&]() { return hypot(h[hs-2].x-h[hs-1].x, h[hs-2].y-h[hs-1].y); };

	auto Put = [&](pp p) {
		while (hs >=2 && !ccw(h[hs-2], h[hs-1], p)) {
			--hs;
			ds -= Hd();
		}
		h[hs++] = p;
		ds += Hd();
	};
	for (int i=n-1; 1<=i; --i) {
		while (nq >= 0 && w[nq].x == i) {
			Put(Qp(nq));
			ans += ds;
			--nq;
		}
		Put(d[i]);
	}

	while (nq >= 0) ans += w[nq].y, --nq;
	static char buf[1024];
	sprintf(buf, "%.1f", ans);
	cout << buf << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	rep(tci, tc) Work();
	return 0;
}
