#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)
#define all(v) v.begin(), v.end()
#define pb push_back
using namespace std;
using ll=long long; using pp=pair<int,int>;
using vi=vector<int>; using vll=vector<ll>;
const int maxn = int(2e5) + 10;

int n;

struct MergeSortTree {
	const static int M = 262144;
	vll t[M<<1];
	void add_point(int x, ll y) { for (x+=M; x; x/=2) t[x].pb(y); }
	void init() {
		for (int i=1; i<M; ++i) sort(all(t[M+i]));
		for (int i=M-1; 1<=i; --i) {
			auto &v = t[i], &vl = t[i*2], &vr = t[i*2+1];
			if (vl.empty()) v = vr; else if (vr.empty()) v = vl;
			else v.resize(vl.size()+vr.size()), merge(all(vl), all(vr), v.begin());
		}
	}
	int rect(int l, int r, ll u) {
		int ret = 0;
		auto qv = [&](vll &v) { ret += (upper_bound(all(v), u)-v.begin()); };
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2==1) qv(t[l++]);
			if (r%2==0) qv(t[r--]);
		}
		return ret;
	}
	int rect(int l, int r, ll d, ll u) {
		int ret = 0;
		auto qv = [&](vll &v) { ret += (upper_bound(all(v), u)-lower_bound(all(v), d)); };
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2==1) qv(t[l++]);
			if (r%2==0) qv(t[r--]);
		}
		return ret;
	}
};

int nxt[maxn], nxtd[maxn];
vi apples[maxn];

namespace Step1 {
int m, L, C;
int person[maxn], apple[maxn];
void In() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> L >> C;
	rrep(i, n) cin >> person[i];
	rrep(i, m) cin >> apple[i];
}

pp GetNxt(int pos) {
	int i = int(upper_bound(person+1, person+n+1, pos)-person)-1;
	if (i == 0) return {n, (L-person[n])+pos};
	else return {i, pos-person[i]};
}

void BuildNxt() {
	rrep(i, n) {
		int t = person[i]-C%L; if (t < 0) t += L;
		tie(nxt[i], nxtd[i]) = GetNxt(t);
		nxtd[i] += C;
	}
}

void AddApples() {
	rrep(i, m) {
		int j, d; tie(j, d) = GetNxt(apple[i]);
		apples[j].emplace_back(d);
	}
}

void Work() {
	In();
	BuildNxt(); AddApples();
}
}

int cn;
int myci[maxn];
int croots[maxn];
ll crdst[maxn];
ll clen[maxn];
vector<int> celem[maxn];
bool iscv[maxn];
int tin[maxn], tout[maxn];

namespace Step2 {
bool onstk[maxn];
void dfs1(int x) {
	onstk[x] = true;
	int y = nxt[x];
	if (!onstk[y]) {
		if (!myci[y]) dfs1(y);
		myci[x] = myci[y];
		crdst[x] = crdst[y] + nxtd[x];
		onstk[x] = false;
		return;
	}
	myci[x] = ++cn; croots[cn] = x; iscv[x] = true;
	celem[cn].pb(x);
	for (int y=nxt[x]; y!=x; y=nxt[y]) celem[cn].pb(y);
	onstk[x] = false;
}

vector<int> child[maxn];
int nt;
void dfs2(int x) {
	tin[x] = ++nt;
	for (int y:child[x]) {
		dfs2(y);
	}
	tout[x] = nt;
}

void BuildGraph() {
	rrep(i, n) if (!myci[i]) dfs1(i);
	rrep(i, n) if (celem[myci[i]][0] != i) child[nxt[i]].pb(i);
	rrep(i, cn) { int r = croots[i];
		for (int x:celem[i]) {
			iscv[x] = true;
			clen[i] += nxtd[x];
		}
		dfs2(r);
	}
}
}

MergeSortTree tconst, tinf;
vector<ll> rdl[maxn], rdp[maxn];
int xoff[maxn], xoz;
ll cp[maxn];

namespace Step3 {
void Build() {
	rrep(i, n) for (int ad:apples[i]) tconst.add_point(tin[i], crdst[i]+ad);
	tconst.init();

	rrep(v, n) for (int ad:apples[v]) rdl[myci[v]].pb(crdst[v]+ad);
	rrep(ci, cn) {
		sort(all(rdl[ci])), rdp[ci].resize(rdl[ci].size());
		xoff[ci] = xoz;
		xoz += rdl[ci].size();
	}

	rrep(v, n) for (int ad:apples[v]) {
		int ci = myci[v];
		auto &vl=rdl[ci], &vp=rdp[ci];
		ll tt = crdst[v] + ad, cl = clen[ci];
		int x = int(lower_bound(all(vl), tt)-vl.begin())+1;

		ll tn = tt/cl, tr = tt%cl;
		tn = -tn-1; tr = cl-tr;
		if (tr == cl) ++tn, tr = 0;

		tinf.add_point(xoff[ci]+x, tr);
		vp[x-1] += tn;
	}

	rrep(ci, cn) partial_sum(all(rdp[ci]), rdp[ci].begin());
	tinf.init();

	rrep(ci, cn) {
		ll pt = 0;
		for (int x:celem[ci]) cp[x]=pt, pt+=nxtd[x];
		cp[celem[ci][0]] = pt;
	}
}
}

int CountConst(int v, ll T) {
	return tconst.rect(tin[v], tout[v], crdst[v]+T);
}

ll CountInf(int v, ll T) {
	int ci = myci[v];
	ll p = cp[v], cl = clen[ci];
	ll np = (T-p)/cl, rp = (T-p)%cl;
	if (rp < 0) rp+=cl, --np;

	auto &vl = rdl[ci], &vp = rdp[ci];
	int xr = upper_bound(all(vl), T-p)-vl.begin();
	if (!xr) return 0;

	ll ret = xr * (1 + np) + (xr ? vp[xr-1] : 0);
	ret += tinf.rect(xoff[ci]+1, xoff[ci]+xr,
		cl-rp, cl);

	return ret;
}

int main() {
	Step1::Work();
	Step2::BuildGraph();
	Step3::Build();

	int q; cin >> q;
for (;q--;) {
	int v; ll T; cin >> v >> T;

	ll ans = CountConst(v, T);
	if (iscv[v]) ans += CountInf(v, T);

	cout << ans;
	cout << '\n';
}
	return 0;
}
