#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using pp=pair<int,int>;
using vi=vector<int>;
const int maxn = int(1e5) + 10;
#define all(v) v.begin(), v.end()
#define pb push_back
#define x first
#define y second

int n;
pp d[maxn];

struct MergeSortTree {
	int n, m; int *xs, **t, *ts;

	void init(int l, int r) {
		n = r-l; for (m=1; m<n; m*=2);
		t = new int*[m*2];
		ts = new int[m*2]{};
		xs = new int[n];
		int *buf = new int[n*(1+__builtin_ctz(m))];

		for (int i=l; i<r; ++i) xs[i-l] = d[i].x;
		sort(xs, xs+n);
		int use = 0;
		for (int i=0, j; i<n; i=j) {
			for (j=i+1; j<n && xs[i]==xs[j]; ++j);
			t[m+i] = buf; buf += j-i;
		}

		for (int i=l; i<r; ++i) {
			int x, y; tie(x, y) = d[i]; x = lower_bound(xs, xs+n, x) - xs;
			x += m;
			t[x][ts[x]++] = y;
		}

		for (int i=m; i<m+n; ++i) sort(t[i], t[i]+ts[i]);

		for (int i=m-1; 1<=i; --i) {
			int l=i*2, r=i*2+1;
			ts[i] = ts[l] + ts[r];
			t[i] = buf; buf += ts[i];
			merge(t[l], t[l]+ts[l], t[r], t[r]+ts[r], t[i]);
		}
	}

	int rect(int l, int r, int d, int u) {
		l = lower_bound(xs, xs+n, l) - xs;
		r = upper_bound(xs, xs+n, r) - xs - 1;
		if (l > r || d > u) return 0;
		int ret = 0;
		auto f = [&](int i) { ret += upper_bound(t[i], t[i]+ts[i], u) - lower_bound(t[i], t[i]+ts[i], d); };
		for (l+=m, r+=m; l<=r; l/=2, r/=2) {
			if (l%2 == 1) f(l++);
			if (r%2 == 0) f(r--);
		}
		return ret;
	}
} mst[262144];

void init(int p, int l, int r) {
	mst[p].init(l, r);
	if (l+1 == r) return;
	int md = (l+r)/2;
	init(p*2, l, md); init(p*2+1, md, r);
}

struct { int l, r, d, u; } Q;
int rect(int sl, int sr, int p, int l, int r) {
	if (sr<=l || r<=sl) return 0;
	if (sl<=l && r<=sr) return mst[p].rect(Q.l, Q.r, Q.d, Q.u);
	int md = (l+r)/2;
	return rect(sl, sr, p*2, l, md) + rect(sl, sr, p*2+1, md, r);
}

bool pcomp(const pp &a, const pp &b) {
	return (a.x+a.y) < (b.x+b.y);
}

int main() { cin.tie(0)->sync_with_stdio(0);
	int q; cin >> n >> q;
	for (int i=0; i<n; ++i) cin >> d[i].x >> d[i].y;
	sort(d, d+n, pcomp);
	init(1, 0, n);

	for(;q--;) {
		int x, y, s; cin >> x >> y >> s;
		int j = lower_bound(d, d+n, pp{s, 0}, pcomp)-d;
		const int inf = int(1e9) + 10;
		Q = {x, inf, y, inf};
		cout << rect(j, n, 1, 0, n) << '\n';
	}
	return 0;
}
