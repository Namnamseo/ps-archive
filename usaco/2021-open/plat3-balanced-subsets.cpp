#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define rep(i, n) for (int i=0; i<(n); ++i)
#define rrep(i, n) for (int i=1; i<=(n); ++i)
const int mod = int(1e9) + 7;
const int maxn = 180;

int n;

int rp[maxn][maxn];
int DP[2][maxn][maxn][16];
auto dp = DP[0], tmp = DP[1];

bool is_full(int row, int l, int r) {
	return (rp[row][r] - rp[row][l-1]) == (r-l+1);
}

int ps[maxn][maxn][16];

void Z(int &x, int y) { x += y; if (x >= mod) x -= mod; }
template<typename... Args>
void Z(int &x, int y, Args... arg) {
	Z(x, y); Z(x, arg...);
}
int Rect(int s, int l, int r, int d, int u) {
	if (r<l || u<d) return 0;
	int t = ps[r][u][s]; Z(t,
		mod-ps[l-1][u][s],
		mod-ps[r][d-1][s],
			ps[l-1][d-1][s]);
	return t;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	rrep(i, n) {
		static char s[maxn];
		cin >> (s+1);
		rrep(j, n) rp[i][j] = rp[i][j-1] + (s[j]=='G');
	}

	int ans = 0;
	rrep(row, n) {
		swap(dp, tmp);
		rrep(i, n) {
			rrep(j, i-1) rep(s, 16) ps[i][j][s] = ps[i-1][j][s];
			for (int j=i; j<=n; ++j) rep(s, 16) {
				int &t = ps[i][j][s];
				t = ps[i][j-1][s]; Z(t,
					ps[i-1][j][s],
				mod-ps[i-1][j-1][s],
					tmp[i][j][s]);
			}
		}

		rrep(l, n) for (int r=l; r<=n; ++r) {
			int *dps = dp[l][r];
			fill(dps, dps+16, 0);
			if (!is_full(row, l, r)) continue;
			dps[0] = 1;
#define Pull(st,bs,bl,br,bd,bu) \
	Z(dps[st], Rect(bs, bl, min(r, br), max(l, bd), bu));

#define Work(st,bs,bl,br) \
	Pull(st*4+ 0, bs*4+ 0, bl, br, r, r); \
	Pull(st*4+ 1, bs*4+ 0, bl, br, r+1, n); \
	Pull(st*4+ 1, bs*4+ 1, bl, br, r, n); \
	Pull(st*4+ 2, bs*4+ 0, bl, br, 1, r-1); \
	Pull(st*4+ 2, bs*4+ 2, bl, br, 1, r); \
	Pull(st*4+ 3, bs*4+ 2, bl, br, r+1, n); \
	Pull(st*4+ 3, bs*4+ 3, bl, br, r, n);

			Work(0, 0, l, l);
			Work(1, 0, l+1, n);
			Work(1, 1, l, n);
			Work(2, 0, 1, l-1);
			Work(2, 2, 1, l);
			Work(3, 1, 1, l-1);
			Work(3, 3, 1, l);

			rep(s, 16) Z(ans, dps[s]);
		}
	}

	cout << ans << '\n';

	return 0;
}

