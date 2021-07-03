#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n, m;

int C[301][301];

int u[301][301][301];

ll dp[301][301];
bool c[301][301];

ll f(int l, int r)
{
	if (l > r) return 0;
	if (c[l][r]) return dp[l][r];
	c[l][r] = 1;
	ll &ret = dp[l][r];
	for (int i=l; i<r; ++i)
		ret = max(ret, f(l, i) + f(i+1, r));
	for (int i=l; i<=r; ++i) {
		int &w = u[i][l][r];
		if (w) {
				ret = max(ret, f(l, i-1) + w + f(i+1, r));
		}
	}

	return ret;
}

int main()
{
	cppio();
	cin >> n >> m;
	for (;m--;) { int w, l, r; cin >> w >> l >> r; for (int i=l; i<=r; ++i) u[i][l][r] = max(u[i][l][r], w); }

	rrep(i, n) {
		rrep(ln, n-1) {
			rrep(l, n-ln+1) {
				int r = l+ln-1;
				if (l-1) u[i][l-1][r] = max(u[i][l-1][r], u[i][l][r]);
				if (r+1<=n) u[i][l][r+1] = max(u[i][l][r+1], u[i][l][r]);
			}
		}
	}

	cout << f(1, n) << endl;
	return 0;
}
