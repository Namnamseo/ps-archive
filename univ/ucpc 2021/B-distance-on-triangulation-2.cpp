#pragma GCC optimize("Ofast,inline")
#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;
const int maxn2 = int(4e5) + 10;

int n;
bitset<maxn2> dirty;
int other[maxn2];

namespace S {
static const int M = 524288;
int tmax[M<<1], tmin[M<<1];
void init() {
	memcpy(tmax+M, other, sizeof(int)*(n+1));
	memcpy(tmin+M, other, sizeof(int)*(n+1));
	for (int i=M-1; 1<=i; --i) {
		tmax[i] = max(tmax[2*i], tmax[2*i+1]);
		tmin[i] = min(tmin[2*i], tmin[2*i+1]);
	}
}
#define seg(tree, func, def) {\
	int ret = def; \
	for (l+=M, r+=M; l<=r; l>>=1, r>>=1) {\
		if (l%2 == 1) ret = func(ret, tree[l++]); \
		if (r%2 == 0) ret = func(ret, tree[r--]); \
	} \
	return ret; }
int rmax(int l, int r) { seg(tmax, max, 0); }
int rmin(int l, int r) { seg(tmin, min, n+1); }
#undef seg
};

void find_dirty() {
	for (int l=1, r; r=other[l], l<=n; ++l) if (l<r) {
		if (S::rmax(l+1, r-1) > r || S::rmin(l+1, r-1) < l) {
			dirty.set(l); dirty.set(r);
		}
	}
}

int is_dirty(int l, int r) {
	int tmp = S::rmax(l+1, r-1);
	if (tmp > r) return tmp;
	tmp = S::rmin(l+1, r-1);
	if (tmp < l) return tmp;
	return 0;
}

pair<int,int> cons[maxn2*3]; int cn;
void con(int a, int b) {
	if (a < 1 || b > n || a == b || a+1 == b || (a == 1 && b == n)) {
		return;
	}
	cons[cn++] = {a, b};
}

void tri(int a, int b, int c) { con(a, b); con(b, c); con(a, c); }

void work_range_clean(int l, int r) {
	if (l > r) return;
	int m = other[l];
	tri(l, m, r+1);
	work_range_clean(l+1, m-1);
	work_range_clean(m+1, r);
}

void enumerate_foots(int l, int r, set<int> &cf) {
	cf.insert(l); cf.insert(other[l]);
	using It=decltype(cf.begin());
	static vector<pair<It,It>> q; q.clear();
	q.emplace_back(cf.begin(), ++cf.begin());
	int hd=0, tl=1, rb=other[l];
	while (hd < tl) {
		It il = q[hd].first, ir=q[hd].second; ++hd;
		if (next(il) != ir) continue;
		int l = *il, r = *ir;
		int pout = is_dirty(l, r); if (!pout) continue;
		int pin = other[pout];
		It iin = cf.insert(pin).first, iout = cf.insert(pout).first;
		q.emplace_back(il, iin);
		q.emplace_back(iin, ir); tl += 2;
		if (rb < pout) {
			q.emplace_back(prev(iout), iout); ++tl;
			rb = pout;
		} else {
			q.emplace_back(prev(iout), iout);
			q.emplace_back(iout, next(iout)); tl += 2;
		}
	}
}

void work_range_general(int l, int r) {
	if (l > r) return;
	int m = other[l];
	if (!dirty[l]) {
		con(l, m);
		if (r == n) con(l, r), con(m, r);
		else con(l-1, m), con(m, r+1);

		work_range_general(l+1, m-1);
		work_range_general(m+1, r);
		return;
	}

	set<int> cf; enumerate_foots(l, r, cf);
	int last = l;
	for (auto it=++cf.begin(); it!=cf.end(); ++it) {
		int f = *it;
		con(l, f);
		con(last, f);
		work_range_general(last+1, f-1);
		last = f;
	}

	if (r == n) con(l-1, last), con(last, r);
	else con(l-1, last), con(last, r+1);

	work_range_general(last+1, r);
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n; n *= 2;
	for (int i=n/2; i--;) {
		int a, b; cin >> a >> b;
		other[a] = b; other[b] = a;
		if (a > b) swap(a, b);
	}

	S::init();
	find_dirty();

	work_range_general(1, n);
	sort(cons, cons+cn);
	cn = unique(cons, cons+cn) - cons;

	int ans = n;
	for (int l=1, r; r=other[l], l<=n; ++l) if (l < r) {
		if (l+1 == r || (l == 1 && r == n)) --ans;
		else {
			auto tmp = make_pair(l, r);
			if (*lower_bound(cons, cons+cn, tmp) == tmp) --ans;
		}
	}

	cout << ans << '\n';
	for (int i=0; i<cn; ++i) cout << cons[i].first << ' ' << cons[i].second << '\n';

	return 0;
}
