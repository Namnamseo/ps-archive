#include <algorithm>
#include <bitset>
#include <iostream>
using namespace std;
using pp=pair<int, int>;
const int maxn = int(3e5) + 10;

int n, q;
char a[2][maxn], apb[maxn];

const int M = 524288;

struct {
	int nt;
	pp t[M<<1];
	void upd(int l, int r, int v) {
		++nt;
		for (l+=M, r+=M; l<=r; (l>>=1), (r>>=1)) {
			if (l&1) { t[l++] = {nt, v}; }
			if (!(r&1)) { t[r--] = {nt, v}; }
		}
	}
	int get(int p) {
		pp ret{0, 0};
		for (p+=M; p; p/=2) ret = max(ret, t[p]);
		return ret.second;
	}
} csnd;

struct {
	bitset<(M<<1)> tree;
	void upd(int p, bool v) {
		tree[p+=M] = v;
		for (;p/=2;) {
			tree[p] = tree[p*2] && tree[p*2+1];
		}
	}
	int first_false(int p) {
		int l = p, r = n+1;
		static int lv[50], rv[50];
		int ln = 0, rn = 0;
		for (l+=M, r+=M; l<=r; l/=2, r/=2) {
			if (l%2 == 1) lv[ln++] = l++;
			if (r%2 == 0) rv[rn++] = r--;
		}
		int t=1;
		for (int i=0; i<ln; ++i) if (t=lv[i], !tree[t]) goto work;
		for (int i=rn-1; 0<=i; --i) if (t=rv[i], !tree[t]) goto work;
		work:
		while (t<M) { t *= 2; if (tree[t]) ++t; }
		return t-M;
	}
} nine;

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	for (int i=0; i<2; ++i) { cin >> (a[i]+1); reverse(a[i]+1, a[i]+n+1); }
	for (int i=1; i<=n; ++i) {
		static bool carry = false;
		apb[i] = (a[0][i] -= '0') + (a[1][i] -= '0');
		carry = (carry && (apb[i] == 9)) || (apb[i] >= 10);
		csnd.upd(i, i, carry);
		if (apb[i] == 9) nine.upd(i, 1);
	}

for(;q--;) {
	int i, df;
	{ char buf[3]; int v;
	cin >> buf >> i >> v;
	char &bef = a[buf[0] == 'B'][i];
	df = v - bef; bef = v; }

	if (df == 0) {
		cout << "0\n";
		continue;
	}

	int bef = apb[i], nxt = bef+df; apb[i] = nxt; nine.upd(i, nxt == 9);
	bool send_bef = csnd.get(i);
	bool send_nxt = (nxt >= 10) || (nxt == 9 && 1 < i && csnd.get(i-1));
	if (send_bef == send_nxt) { cout << "1\n"; continue; }

	int to = nine.first_false(i+1);
	csnd.upd(i, to-1, send_nxt);
	cout << (to-i+1) << '\n';
}

	return 0;
}
