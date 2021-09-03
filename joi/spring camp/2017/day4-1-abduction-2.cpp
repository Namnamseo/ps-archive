#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
template<typename T,typename U>
istream& operator>>(istream& i, pair<T,U>& p) { i >> p.first >> p.second; return i; }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()
#define XY(t) t.x, t.y

const ll inf = 1ll<<60;

int n, m, q;

int ca[50010];
int cb[50010];

int mxl[2][16][50010];
int mxr[2][16][50010];

int sz[2];

void Pre() {
	sz[0] = n; sz[1] = m;
	{
		int t=0, sz=n;
		for(int *a:{ca, cb}) {
			auto vl=mxl[t], vr=mxr[t];
			rrep(i, sz) vl[0][i] = vr[0][i] = a[i];
			rrep(i, 15) { int hw = 1<<(i-1); rrep(j, sz) {
				vl[i][j] = (j > hw) ? max(vl[i-1][j], vl[i-1][j-hw]) : vl[i-1][j];
				vr[i][j] = (j+hw <= sz) ? max(vr[i-1][j], vr[i-1][j+hw]) : vr[i-1][j];
			} }
			sz += m-n; ++t;
		}
	}
}

pp G(int x, int y, int d, int th=0) {
	int e = d^1;
	int l, r;
	if (d == 0) l=r=y; else l=r=x;
	int v = (d?cb:ca)[x+y-l];

	l-=th;
	for(int i=15; 0<=i && l>=1; --i) {
		if (mxl[e][i][l] <= v) {
			l -= (1<<i);
			if (l < 1) { l = 0; break; }
		}
	}

	r+=th;
	for(int i=15; 0<=i && r<=sz[e]; --i) {
		if (mxr[e][i][r] <= v) {
			r += (1<<i);
			if (r > sz[e]) { r = sz[e]+1; break; }
		}
	}

	return {l, r};
}

ll ans;

void f(int mn, int l, int r,
	ll dld, ll dlu,
	ll drd, ll dru, int d) {

	int sm = d ? n : m;
	if (l == 0) {
		ans = max(ans, max(dld, dlu)-1);
		if (r > sm) {
			ans = max(ans, max(drd, dru)-1);
			return;
		}
		pp t = G(d?r:mn, d?mn:r, d^1);
		f(r, t.x, t.y,
			dru+(mn-t.x),
			dru+(mn-t.x),
			drd+(t.y-mn),
			drd+(t.y-mn),
			d^1); return;
	}
	if (r > sm) {
		ans = max(ans, max(drd, dru)-1);
		pp t = G(d?l:mn, d?mn:l, d^1);
		f(l, t.x, t.y,
			dlu+(mn-t.x),
			dlu+(mn-t.x),
			dld+(t.y-mn),
			dld+(t.y-mn),
			d^1); return;
	}

	pp fl = G(d?l:mn, d?mn:l, d^1);
	pp fr = G(d?r:mn, d?mn:r, d^1);

	ll dlx = dlu+mn-fl.x, dly=dld+fl.y-mn;
	ll drx = dru+mn-fr.x, dry=drd+fr.y-mn;

	if (fl == fr) {
		if (fl.x == 0) {
			if (fl.y > sz[d]) {
				ans = max(ans,
					max({dlx, dly, drx, dry})-1);
				return;
			}
			ans = max(ans, max(dlx, drx)-1);
			dlx = drx = -inf;
		} else if (fl.y > sz[d]) {
			ans = max(ans, max(dly, dry)-1);
			dly = dry = -inf;
		}
		f(l, fl.x, fl.y,
			dlx, drx+r-l,
			dly, dry+r-l, d^1);
		return;
	} else {
		int wl = fl.y-fl.x, wr = fr.y-fr.x;
		if (wl < wr) {
			f(l, fl.x, fl.y, dlx, dlx, dly, dly, d^1);
		} else {
			f(r, fr.x, fr.y, drx, drx, dry, dry, d^1);
		}
		return;
	}
}

void O(int x, int y, int d)
{
	int tv = d?cb[y]:ca[x];
	int ov = d?ca[x]:cb[y];
	pp g = G(x, y, d, 1);
	int X=x, Y=y; if (d) swap(X, Y);
	if (tv > ov) {
		f(X, g.x, g.y, Y-g.x, Y-g.x, g.y-Y, g.y-Y, d);
	} else {
		f(X, g.x, Y, Y-g.x, Y-g.x, -inf, -inf, d);
		f(X, Y, g.y, -inf, -inf, g.y-Y, g.y-Y, d);
	}
}

int main()
{
	cppio(); cin>>n>>m>>q; rrep(i, n) cin>>ca[i]; rrep(i, m) cin>>cb[i];
	Pre();
for(;q--;) {
	int x, y; cin>>x>>y;
	ans = 0; rep(j, 2) O(x, y, j);
	cout << ans << '\n';
}
	return 0;
}
