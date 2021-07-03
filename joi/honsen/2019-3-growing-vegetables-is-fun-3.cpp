#include <iostream>
#include <algorithm>
using namespace std;
#define rep(i, n) for (int i=0; i<n; ++i)
#define rrep(i, n) for (int i=1; i<=n; ++i)

const int maxn = 400 + 10;
const int inf = int(1e9) + 10;

int n;
char s[maxn];
int ps[maxn][3];
int pos[3][maxn];
int dp[maxn][maxn][maxn][3];

int ma, mb, mc;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> (s+1);
	rrep(i, n) {
		rep(j, 3) ps[i][j] = ps[i-1][j];
		pos[s[i]%4-1][++ps[i][s[i]%4-1]] = i;
	}

	ma = ps[n][0];
	mb = ps[n][1];
	mc = ps[n][2];

	rrep(S, n) {
	for (int a=0; a<=S && a<=ma; ++a) {
	for (int b=0; b<=S-a && b<=mb; ++b) {
	int c = S-a-b; if (c>mc) continue;
		int *d = dp[a][b][c]; rep(i, 3) d[i] = inf;
		int is[3] = {a, b, c};
		rep(ui, 3) { if (!is[ui]) continue;
			int bm = inf;
			{
				--is[ui];
				int *bef = dp[is[0]][is[1]][is[2]];
				++is[ui];
				rep(bi, 3) if (ui != bi && bef[bi] != inf) bm = min(bm, bef[bi]);
			}
			if (bm == inf) continue;
			int df = 0;
			int ci = pos[ui][is[ui]];
			rep(oc, 3) if (oc != ui) {
				int cu = ps[ci][oc];
				int cd = is[oc];
				df += abs(cu-cd);
			}
			d[ui] = min(d[ui], bm + df);
		}
	}
	}
	}

	int *aa = dp[ma][mb][mc];
	int ans = *min_element(aa, aa+3);
	if (ans == inf) ans = -1;
	else ans /= 2;
	cout << ans << '\n';

	return 0;
}
