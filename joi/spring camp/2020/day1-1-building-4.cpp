#include <iostream>
using namespace std;

int main() { cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n; n *= 2;
	const int maxn = int(1e6) + 10;
	static int A[maxn], B[maxn];
	for (int i=1; i<=n; ++i) cin >> A[i];
	for (int i=1; i<=n; ++i) cin >> B[i];

	const int inf = int(1e9);
	static int dp[maxn][4];
	dp[0][2] = -inf; dp[0][3] = inf;
	for (int i=1; i<=n; ++i) {
		int v[2] = {A[i], B[i]};
		for (int j=0; j<2; ++j) {
			int &dmx = dp[i][2*j], &dmn = dp[i][2*j+1];
			dmx = -inf;
			dmn = inf;
			int bv[2] = {A[i-1], B[i-1]};
			for (int bj=0; bj<2; ++bj) if (bv[bj]<=v[j]) {
				int bmx = dp[i-1][2*bj], bmn = dp[i-1][2*bj+1];
				dmx = max(dmx, bmx + j);
				dmn = min(dmn, bmn + j);
			}
		}
	}

for (int j=0; j<2; ++j) {
	int dmx = dp[n][2*j], dmn = dp[n][2*j+1];
	if (dmn <= (n/2) & (n/2) <= dmx) {
		static char ans[maxn];
		for (int ci=n, cj=j, cd=n/2;;) {
			ans[ci] = 'A'+cj;
			if (ci == 1) break;
			int cv[2] = {A[ci], B[ci]}, bv[2] = {A[ci-1], B[ci-1]};
			for (int bj=0; bj<2; ++bj) if (bv[bj] <= cv[cj]) {
				int bd = (cd - cj);
				if (dp[ci-1][2*bj+1] <= bd && bd <= dp[ci-1][2*bj]) {
					--ci;
					cj = bj;
					cd = bd;
					break;
				}
			}
		}
		cout << (ans+1) << '\n';
		return 0;
	}
}

	cout << "-1\n";
	return 0;
}
