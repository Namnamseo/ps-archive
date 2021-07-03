#include <algorithm>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;
using pp=pair<int, int>;
#define x first
#define y second
#define rep(i, n) for(int i=0; i<(n); ++i)

const int maxn = 50;
const int mod = int(1e9) + 7;

int n;
pp d[maxn];

int Side(pp a, pp b, pp c) {
	return (c.x-a.x)*(b.y-a.y) >= (c.y-a.y)*(b.x-a.x);
}

bool Inside(int i, int j, int k, int t) {
	return i!=t && j!=t && k!=t && (
		Side(d[i], d[j], d[t]) +
		Side(d[j], d[k], d[t]) +
		Side(d[k], d[i], d[t])
		) % 3 == 0;
}

pair<int*, int> Insides(int i, int j, int k) {
	static int mv[maxn][maxn][maxn][maxn];
	static int mn[maxn][maxn][maxn];
	static bool vis[maxn][maxn][maxn];
	if (i>j) swap(i, j); if (j>k) swap(j, k); if (i>j) swap(i, j);

	int *arr = mv[i][j][k], &an = mn[i][j][k];
	if (!vis[i][j][k]) {
		vis[i][j][k] = true;
		rep(t, n) if (t!=i && t!=j && t!=k && Inside(i, j, k, t)) {
			int i3[3] = {i, j, k};
			arr[an++] = t;
			rep(vi, 3) {
				auto [narr, nn] = Insides(i3[vi], i3[(vi+1)%3], t);
				copy(narr, narr+nn, arr+an);
				an += nn;
			}
			break;
		}
	}

	return {arr, an};
}

int Encode(int a, int b, int c, int d) { return d+n*(c+n*(b+n*a)); }

int Ways(int i, int j, int k, int internals)
{
	auto [ia, in] = Insides(i, j, k);
	if (internals > in) return 0;

	static int mem[maxn*maxn*maxn*maxn];
	static bool vis[maxn*maxn*maxn*maxn];

	int key = Encode(i, j, k, internals);
	int &ret = mem[key];
	if (vis[key]) return ret;
	vis[key] = true;

	ret = Ways(i, j, k, internals+1) * 1ll * (internals+1) % mod;
	if (internals == in) {
		ret += 6;
		if (ret >= mod) ret -= mod;
	}

rep(ii, in) {
	int t = ia[ii];

	int cnt[6];
	int ijk[6] = {i, j, k, i, j, k};
	rep(z, 3) {
		int a = ijk[z], b = ijk[z+1], c = t;
		cnt[z] = cnt[z+3] = Insides(a, b, c).y;
	}

	rep(z, 3) {
		int news = cnt[z] + cnt[z+2];
		if (internals >= news) {
			ret += Ways(t, ijk[z+1], ijk[z+2], internals - news);
			if (ret >= mod) ret -= mod;
		}
	}
}

	return ret;
}

int main()
{
	cin >> n; for (int i=0; i<n; ++i) cin >> d[i].x >> d[i].y;

	auto [i, j, k] = [&]()->tuple<int,int,int>{
		rep(i, n) rep(j, i) rep(k, j) if (Insides(i, j, k).y == n-3) {
			return {i, j, k};
		}
		return {-1, -1, -1};
	}();

	if (i == -1) {
		cout << "0\n";
		return 0;
	}

	cout << Ways(i, j, k, 0) << '\n';


	return 0;
}
