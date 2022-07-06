#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <cstring>
#include <iostream>
using namespace std;
using ll=long long;

const int maxn = int(1e2) + 10;
const int maxk = int(1e3) + 10;
const ll inf = 0x3f3f3f3f * ((1ll<<32)+1);

int n, m, knd;
int buy[maxn][maxk], sell[maxn][maxk];
ll de[maxn][maxn];
int mxsell[maxn][maxn];

#define Floyd(d) { \
	for (int j=1; j<=n; ++j) { \
		for (int i=1; i<=n; ++i) for (int k=1; k<=n; ++k) \
			d[i][k] = min(d[i][k], d[i][j] + d[j][k]); \
	} \
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m >> knd;
	n &= 127;
	for (int i=1; i<=n; ++i) for (int j=1; j<=knd; ++j) {
		cin >> buy[i][j] >> sell[i][j];
	}
	memset(de, 0x3f, sizeof(de));
	for (int i=1; i<=m; ++i) {
		int f, t, v; cin >> f >> t >> v;
		de[f][t] = min(de[f][t], ll(v));
	}
	Floyd(de);

	for (int t=1; t<=knd; ++t) {
		for (int i=1; i<=n; ++i) if (buy[i][t] != -1)
		for (int j=1; j<=n; ++j) if (sell[j][t] != -1) {
			mxsell[i][j] = max(mxsell[i][j], sell[j][t]-buy[i][t]);
		}
	}

	int ql=-1, qr=int(1e9)+10;
	while (ql+1 < qr) {
		int c = (ql+qr)/2;
		static ll dc[maxn][maxn];
		for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
			if (de[i][j] == inf) dc[i][j] = inf;
			else dc[i][j] = c*1ll*de[i][j]-mxsell[i][j];
		}
		Floyd(dc);
		bool loop = false;
		for (int i=1; i<=n; ++i) if (dc[i][i] <= 0) { loop = true; break; }
		(loop ? ql : qr) = c;
	}

	cout << ql << '\n';

	return 0;
}
