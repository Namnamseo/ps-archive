#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <tuple>
#define x first
#define y second
using namespace std;
using pp=pair<int, int>;
using ppp=pair<pp, pp>;
using ll=long long;
const int maxn = 512;

pp d[maxn];
int n;
int xi[maxn], yi[maxn];
int xr[maxn], yr[maxn];

ppp Work(pp a, pp b) {
	bool bb = (b < a);
	int dx = (b.x-a.x), dy = (b.y-a.y);
	ll gj; { int mx = (b.x+a.x), my = (b.y+a.y); gj = ((dx*1ll*mx + dy*1ll*my)>>1); }

	int cmn[2] = {0, 0};
	static short cs[2][2][maxn];
	memset(cs[0][0], 0, sizeof(short)*n);
	memset(cs[0][1], 0, sizeof(short)*n);
	memset(cs[1][0], 0, sizeof(short)*n);
	memset(cs[1][1], 0, sizeof(short)*n);
	for (int i=0; i<n; i++) {
		ll me = d[i].x*1ll*dx + d[i].y*1ll*dy - gj;
		bool v = (me > 0) || (me == 0 && bb);
		cs[v][0][xi[i]]++;
		cs[v][1][yi[i]]++;
		++cmn[v];
	}

	pp cnew[2];
	for (int ci=0, s; s=cmn[ci], ci<2; ++ci) {
		int ti, rs;
		int k1=(s-1)/2, k2=s/2;
		int xs=0, ys=0;
		ti=rs=0; while (rs+cs[ci][0][ti] <= k1) rs+=cs[ci][0][ti], ++ti; xs += xr[ti];
		while (rs+cs[ci][0][ti] <= k2) rs+=cs[ci][0][ti], ++ti; xs += xr[ti];
		ti=rs=0; while (rs+cs[ci][1][ti] <= k1) rs+=cs[ci][1][ti], ++ti; ys += yr[ti];
		while (rs+cs[ci][1][ti] <= k2) rs+=cs[ci][1][ti], ++ti; ys += yr[ti];
		cnew[ci] = {xs/2, ys/2};
	}
	sort(cnew, cnew+2);
	return {cnew[0], cnew[1]};
}

map<ppp, pair<int,ppp>> dp;

pair<int,ppp> f(pp a, pp b) {
	auto key = make_pair(a, b);
	auto &ret = dp[key];
	if (ret.x) return ret;

	auto nxt = Work(a, b);
	if (nxt == key) {
		return ret = {0, key};
	}

	ret = f(nxt.x, nxt.y);
	++ret.x;
	return ret;
}

map<ppp, pair<ll,int>> fdp;
int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	for (int i=0; i<n; ++i) { cin >> d[i].x >> d[i].y; d[i].x *= 2; d[i].y *= 2; }
	{
		for (int i=0; i<n; ++i) xr[i]=d[i].x, yr[i]=d[i].y;
		sort(xr, xr+n); sort(yr, yr+n);
		int xn = unique(xr, xr+n)-xr, yn = unique(yr, yr+n)-yr;
		for (int i=0; i<n; ++i) xi[i]=lower_bound(xr, xr+xn, d[i].x)-xr, yi[i]=lower_bound(yr, yr+yn, d[i].y)-yr;
	}

	for (int i=0; i<n; ++i) for (int j=0; j<i; ++j) {
		auto nxt = Work(d[i], d[j]);
		if ((d[i] < d[j] && nxt == make_pair(d[i], d[j])) || nxt == make_pair(d[j], d[i])) {
			auto &acc = fdp[nxt];
			acc.x++; acc.y++;
			continue;
		}
		auto [steps, ending] = f(nxt.x, nxt.y);
		auto &acc = fdp[ending];
		acc.x += steps+2;
		acc.y++;
	}

	cout.precision(10);
	for (auto &item:fdp) {
		double avg = double(item.y.x) / item.y.y;
		int x, y;
		tie(x, y) = item.x.x;
		if (x==-1) cout << '-'; cout << (x/2) << '.' << ((x&1)?'5':'0') << ' ';
		if (y==-1) cout << '-'; cout << (y/2) << '.' << ((y&1)?'5':'0') << ' ';
		tie(x, y) = item.x.y;
		if (x==-1) cout << '-'; cout << (x/2) << '.' << ((x&1)?'5':'0') << ' ';
		if (y==-1) cout << '-'; cout << (y/2) << '.' << ((y&1)?'5':'0') << ' ';
		cout << fixed << avg << '\n';
	}

	return 0;
}
