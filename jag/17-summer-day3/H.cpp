#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
#define x first
#define y second
#define xy(a) a.x, a.y
#define all(v) v.begin(), v.end()
using namespace std;
using pp=pair<int,int>;
using ll=long long;

pp operator-(const pp& a, const pp& b) { return {b.x-a.x, b.y-a.y}; }
bool ccw(const pp& a, const pp& b, const pp& c) {
	return ((b.x-a.x)*1ll*(c.y-a.y)) >= ((b.y-a.y)*1ll*(c.x-a.x));
}

bool ccw(const pp& a, const pp& b) {
	return a.x*1ll*b.y > a.y*1ll*b.x;
}

vector<pp> hull_part(const vector<pp> &v) {
	vector<pp> ret; int sz = 0;
	for (auto &p : v) {
		while (sz >= 2 && ccw(ret[sz-2], ret[sz-1], p))
			ret.pop_back(), --sz;
		ret.push_back(p); ++sz;
	}
	return ret;
}

vector<pp> hull(vector<pp> v) {
	sort(all(v)); auto hu = hull_part(v);
	reverse(all(v)); auto hd = hull_part(v);
	hu.pop_back(); hu.insert(hu.end(), all(hd)-1);
	return hu;
}

int H, W, R;

int gcd(int a, int b) { while (b) a%=b, swap(a, b); return a; }
pp Reg(pp p) {
	int g = gcd(abs(p.x), abs(p.y));
	return {p.x/g, p.y/g};
}
pp Rot(pp p) { return {-p.y, p.x}; }

int n;
vector<pp> v;

ll Dot(const pp &a, const pp &b) { return a.x*1ll*b.x + a.y*1ll*b.y; }
int Prv(int i) { return i ? (i-1) : (n-1); }
int Nxt(int i) { return (i == n-1) ? 0 : (i+1); }

bool IsPeak(pp dir, int i) {
	const pp &a = v[Prv(i)], &b = v[i], &c = v[Nxt(i)];
	ll va = Dot(dir, a), vb = Dot(dir, b), vc = Dot(dir, c);
	return va <= vb && vb >= vc;
}

double Haba(pp v, double dx, double dy) {
	return abs(v.x*dx + v.y*dy) / hypot(dx, dy);
}

pair<double, double> Range(pp v, pp d0, pp d1, int lim) {
	double h0 = Haba(v, d0.x, d0.y);
	double h1 = Haba(v, d1.x, d1.y);
	if (h0 <= lim && h1 <= lim) return {0., 1.};
	if (h0 > lim && h1 > lim) return {1., 0.};
	if (h0 <= lim) {
		double l=0, r=1;
		for (int i=0; i<30; ++i) {
			double m = (l+r)/2;
			if (Haba(v, d0.x*(1-m) + d1.x*m, d0.y*(1-m) + d1.y*m) <= lim) l = m;
			else r = m;
		}
		return {0., r};
	} else {
		double l=0, r=1;
		for (int i=0; i<30; ++i) {
			double m = (l+r)/2;
			if (Haba(v, d0.x*(1-m) + d1.x*m, d0.y*(1-m) + d1.y*m) <= lim) r = m;
			else l = m;
		}
		return {l, 1.};
	}
}

bool Search(pp d0, pp d1, int idx[4]) {
	int hh = H, ww = W;
	auto v1 = v[idx[0]]-v[idx[2]], v2 = v[idx[1]]-v[idx[3]];
	v2 = {v2.y, -v2.x};
for (int rep=0; rep<2; ++rep) { swap(hh, ww);
	auto r1 = Range(v1, d0, d1, hh), r2 = Range(v2, d0, d1, ww);
	if (max(r1.x, r2.x) <= min(r1.y, r2.y)) return true;
}
	return false;
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> H >> W >> R; H -= 2*R; W -= 2*R;
	if (n == 1) {
		cout << ((H >= 0 && W >= 0)?"Yes":"No") << '\n';
		return 0;
	}

	v.resize(n); for (auto &p:v) cin >> p.x >> p.y;
	v = hull(v); n = v.size();
	reverse(all(v));

	if (n == 2) {
		cout << (((hypot(H, W) >= hypot(v[0].x-v[1].x, v[0].y-v[1].y)))?"Yes":"No") << '\n';
		return 0;
	}

	vector<pp> edges(n);
	for (int i=0; i<n; ++i) {
		pp p = v[(i+1)%n] - v[i];
		for (;;) {
			if (p.x > 0 && p.y >= 0) break;
			p = Rot(p);
		}
		edges[i] = Reg(p);
	}

	sort(all(edges), (bool(&)(const pp&, const pp&)) ccw);
	edges.erase(unique(all(edges)), edges.end());

	int idx[4] = {0, 0, 0, 0};

	for (int i=0, j=0; i<4; ++i) {
		pp d = edges[0]; for (int k=0; k<i; ++k) d = Rot(d);
		j = 0; while (!IsPeak(d, j) || IsPeak(d, Nxt(j))) j = Nxt(j);
		idx[i] = j;
	}

	{ int dx, dy; tie(dx, dy) = edges[0];
	edges.emplace_back(-dy, dx); }
	for (int i=0, s=edges.size()-1u; i<s; ++i) {
		pp d0 = edges[i], d1 = edges[i+1];
		{ pp tmp = d0; for (int j=0; j<4; tmp=Rot(tmp), ++j) {
			int &ii = idx[j];
			while (!IsPeak(tmp, ii) || IsPeak(tmp, Nxt(ii))) ii = Nxt(ii);
		} }
		if (Search(d0, d1, idx)) {
			cout << "Yes\n";
			return 0;
		}
	}

	cout << "No\n";
	return 0;
}
