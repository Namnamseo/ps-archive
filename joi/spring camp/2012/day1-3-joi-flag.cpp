#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
using ll=long long;
const int maxn = int(1e3) + 10;
const int inf = int(1e9);

int k;
int n;
pair<ll,char> d[maxn];

int f(int dl, int dr, int lev, ll kl=0) {
	if (dl >= dr || !lev) return 0;
	int ret = inf;

	ll base = 1ll << (2*(lev-1));
	int kps[5];
	for (int i=0, cp=dl; i<=4; ++i) {
		ll t = kl+base*i;
		for (;cp<dr && d[cp].first < t;) ++cp;
		kps[i] = cp;
	}

	int costs[4][4] = {};
	for (int gi=0; gi<4; ++gi) { int gl=kps[gi], gr=kps[gi+1];
		for (int si=0; si<3; ++si) costs[gi][si] = (gr-gl);
		for (int i=gl; i<gr; ++i) --costs[gi][d[i].second];
		costs[gi][3] = f(gl, gr, lev-1, kl+base*gi);
	}

#define P4(a,b,c,d) P3(a,b,c,d) P3(b,c,d,a) P3(c,d,a,b) P3(d,a,b,c)
#define P3(a,b,c,d) P2(a,b,c,d) P2(a,c,d,b) P2(a,d,b,c)
#define P2(a,b,c,d) P1(a,b,c,d) P1(a,b,d,c)
#define P1(a,b,c,d) ret = min(ret, costs[0][a]+costs[1][b]+costs[2][c]+costs[3][d]);
	P4(0,1,2,3);

	return ret;
}

int main() { cin.tie(0)->sync_with_stdio(0);
	cin >> k >> n;
	for (int i=0; i<n; ++i) {
		int x, y; cin >> y >> x;
		static char buf[5]; cin >> buf;
		ll key = 0;
		--x; --y;
		for (int b=k-1; 0<=b; --b) {
			key = (key<<1) | (1&(x>>b));
			key = (key<<1) | (1&(y>>b));
		}
		d[i] = {key, (buf[0] == 'J') ? 0 : (buf[0] == 'O') ? 1 : 2};
	}
	sort(d, d+n);

	cout << f(0, n, k) << '\n';

	return 0;
}
