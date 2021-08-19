#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
const int maxn = int(5e2) + 10;

int n;

int c[maxn];
int a[maxn];
int v[maxn];

bool ok(int i, int j) { return !i || !j || c[i]==c[j] || a[i]==a[j]; }

int f1(int start, int last);
int f2(int s2, int soth);
int f3(int s1, int soth, int last);
int f4(int sa, int sb, int soth);

// [*]
int f1(int start, int last) {
	static int dp[maxn][maxn]; static bitset<maxn> vis[maxn];
	int &ret = dp[start][last];
	if (vis[start][last]) return ret;
	vis[start][last] = 1;

	int i = start;
	if (i <= n && ok(last, i)) {
		ret = max(ret, v[i] + f1(start+1, i));
	}

	i = start + 2;
	if (i <= n && ok(last, i)) {
		ret = max(ret, v[i] + f2(start, i+1));
	}

	return ret;
}

// 2, *, [*]
// last: soth-1
int f2(int s2, int soth) {
	static int dp[maxn][maxn]; static bitset<maxn> vis[maxn];
	int &ret = dp[s2][soth];
	if (vis[s2][soth]) return ret;
	vis[s2][soth] = 1;
	const int last = soth-1;

	int i = s2;
	if (ok(last, i)) {
		ret = max(ret, v[i] + f3(i+1, soth, i));
	}

	i = soth;
	if (i <= n && ok(last, i)) {
		ret = max(ret, v[i] + f2(s2, i+1));
	}

	return ret;
}

// 1, *, [*]
int f3(int s1, int soth, int last) {
	static int dp[maxn][maxn][maxn]; static bitset<maxn> vis[maxn][maxn];
	int &ret = dp[s1][soth][last];
	if (vis[s1][soth][last]) return ret;
	vis[s1][soth][last] = 1;

	int i = s1;
	if (ok(last, i)) {
		ret = max(ret, v[i] + f1(soth, i));
	}

	i = soth+1;
	if (i <= n && ok(last, i)) {
		ret = max(ret, v[i] + f4(s1, soth, i+1));
	}

	return ret;
}

// 1, *, 1, *, [*]
// last: soth-1
int f4(int sa, int sb, int soth) {
	static int dp[maxn][maxn][maxn]; static bitset<maxn> vis[maxn][maxn];
	int &ret = dp[sa][sb][soth];
	if (vis[sa][sb][soth]) return ret;
	vis[sa][sb][soth] = 1;
	const int last = soth-1;

	int i = sa;
	if (ok(last, i)) {
		ret = max(ret, v[i] + f3(sb, soth, i));
	}

	i = soth;
	if (i <= n && ok(last, i)) {
		ret = max(ret, v[i] + f4(sa, sb, i+1));
	}

	return ret;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n;
	for (int i=1; i<=n; ++i) cin >> c[i] >> a[i] >> v[i];

	cout << f1(1, 0) << '\n';

	return 0;
}
