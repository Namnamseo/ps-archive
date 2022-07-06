#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using ll=long long;
using pp=pair<int,int>;
const int maxn = int(2e5) + 10;

int n;
int a[maxn];

pair<pp,int> gnum[maxn];

namespace {
	const int M = 262144;
	pp t[M<<1];

	void build() {
		for (int i=1; i<=n; ++i) t[M+i] = {a[i], i};
		for (int i=M-1; 1<=i; --i) t[i] = max(t[i*2], t[i*2+1]);
	}

	int maxi(int l, int r) {
		pp mx{};
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2 == 1) mx = max(mx, t[l++]);
			if (r%2 == 0) mx = max(mx, t[r--]);
		}
		return mx.second;
	}

	int wrap_v(int x, int y) {
		int l = x, r = x;
		static int vs[40], vn;
		auto Enum = [&](int l, int r) {
			static int vl[20], vr[20];
			int vln = 0, vrn = 0;
			for (l+=M, r+=M; l<=r; l/=2, r/=2) {
				if (l%2 == 1) vl[vln++] = l++;
				if (r%2 == 0) vr[vrn++] = r--;
			}
			vn = 0;
			copy(vl, vl+vln, vs); vn += vln;
			for (int i=vrn-1; 0<=i; --i) vs[vn++] = vr[i];
		};
		Enum(1, l-1);
		int lok = vn; while (lok && t[vs[lok-1]].first < y) --lok;
		if (lok-1 >= 0) {
			for (l = vs[lok-1]; l<M;) {
				if (t[l*2+1].first < y) l *= 2;
				else l = l*2+1;
			}
			l = l+1 - M;
		} else l = 1;
		Enum(r+1, n);
		lok = -1; while (lok+1<vn && t[vs[lok+1]].first < y) ++lok;
		if (lok+1 < vn) {
			for (r = vs[lok+1]; r<M;) {
				if (t[r*2].first < y) r = r*2+1;
				else r *= 2;
			}
			r = r-1 - M;
		} else r = n;
		return lower_bound(gnum, gnum+n, pair<pp, int>{{l, r}, -1})->second;
	}
}

vector<int> te[maxn];
int root;
vector<pp> paths[maxn];
int gdfs(int l, int r) {
	static int gn;
	int me = ++gn; gnum[gn-1] = {{l, r}, me};
	if (l == r) return me;
	int i = maxi(l, r);
	if (l < i) te[me].push_back(gdfs(l, i-1));
	if (i < r) te[me].push_back(gdfs(i+1, r));
	return me;
}

int tin[maxn], tout[maxn], nt;
void tdfs1(int x) {
	tin[x] = ++nt; for (int y : te[x]) tdfs1(y); tout[x] = nt;
}

ll dp[maxn];
struct It {
	const static int M = 262144;
	ll t[M<<1];
	void upd(int l, int r, ll v) {
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2==1) t[l++] += v;
			if (r%2==0) t[r--] += v;
		}
	}
	ll get(int p) { ll ret = 0;
		for (p+=M; p; p/=2) ret += t[p];
		return ret;
	}
} giveup;

void tdfs2(int x) {
	ll cds = 0;
	for (int y:te[x]) tdfs2(y), cds += dp[y];
	ll mdf = 0;
	for (auto &tmp:paths[x]) {
		int to, c; tie(to, c) = tmp;
		mdf = max(mdf, c + giveup.get(tin[to]));
	}
	dp[x] = cds + mdf;
	giveup.upd(tin[x], tout[x], -mdf);
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n; for (int i=1; i<=n; ++i) cin >> a[i];
	build();

	ll csum = 0;
	root = gdfs(1, n);
	sort(gnum, gnum+n);
	{ int m; cin >> m;
	for (;m--;) {
		int x, y, c; cin >> x >> y >> c; csum += c;
		int up = wrap_v(x, y), down = wrap_v(x, a[x]+1);
		paths[up].push_back({down, c});
	} }

	tdfs1(root);
	tdfs2(root);

	ll ans = csum - dp[root];
	cout << ans << '\n';

	return 0;
}
