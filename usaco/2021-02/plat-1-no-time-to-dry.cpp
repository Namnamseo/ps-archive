#include <iostream>
using namespace std;
const int maxn = int(2e5) + 10;
const int maxv = 524288 + 20*maxn;

int n, q;
int a[maxn];

int nn; int nl[maxv], nr[maxv], nv[maxv];
int build(int l, int r) {
	int me = ++nn;
	if (l == r) return me;
	int mid = (l+r)/2;
	nl[me] = build(l, mid);
	nr[me] = build(mid+1, r);
	return me;
}

int upd(int o, int p, int v, int l, int r) {
	if (p<l || r<p) return o;
	int me = ++nn;
	if (l == r) {
		nv[me] = nv[o] + v;
	} else {
		int mid = (l+r)/2;
		nl[me] = upd(nl[o], p, v, l, mid);
		nr[me] = upd(nr[o], p, v, mid+1, r);
		nv[me] = nv[nl[me]] + nv[nr[me]];
	}
	return me;
}

int qry(int p, int l, int r, int ml, int mr) {
	if (r < ml || mr < l) return 0;
	if (l <= ml && mr <= r) return nv[p];
	int mid = (ml+mr)/2;
	return qry(nl[p], l, r, ml, mid) + qry(nr[p], l, r, mid+1, mr);
}

int rt[maxn];
void Proc() {
	static int stk[maxn], top;
	static int pt[maxn];
	for (int i=1; i<=n; ++i) {
		while (top && a[stk[top-1]] > a[i]) --top;
		if (top && a[stk[top-1]] == a[i]) {
			pt[stk[top-1]] = i;
			--top;
		}
		stk[top++] = i;
	}

	rt[0] = build(1, n);
	for (int i=1; i<=n; ++i) {
		rt[i] = rt[i-1];
		if (pt[i]) {
			rt[i] = upd(rt[i], pt[i], 1, 1, n);
		}
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> q;
	for (int i=1; i<=n; ++i) cin >> a[i];

	Proc();

	for(;q--;) {
		int l, r; cin >> l >> r;
		int ans = qry(rt[r], 1, r, 1, n) - qry(rt[l-1], 1, r, 1, n);
		ans = (r-l+1) - ans;
		cout << ans << '\n';
	}

	return 0;
}
