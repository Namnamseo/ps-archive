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
#define XY(t) t.x, t.y

const int maxn = int(1e5) + 10;

int n, k;
pp a[maxn];
int x[maxn], xn;

void zip()
{
	rrep(i, n) x[xn++] = a[i].x, x[xn++] = a[i].y; sort(x, x+xn);
	auto f = [&](int &p) { p = int(lower_bound(x, x+xn, p)-x); };
	rrep(i, n) f(a[i].x), f(a[i].y);
}

void inc()
{
	sort(a+1, a+n+1);
	int ly = -1, j = 0;
	rrep(i, n) {
		if (ly > a[i].y) { --k; }
		else {
			if (i != ++j) a[j] = a[i];
			ly = a[i].y;
		}
	}
	n = j;
	if (k <= 0) {
		static int ps[maxn*2];
		rrep(i, n) {
			++ps[a[i].x];
			--ps[a[i].y];
		}
		rrep(i, 2*n-1) ps[i]+=ps[i-1];
		ll ans = 0;
		rrep(i, 2*n-1) ans += ll(ps[i-1])*(x[i]-x[i-1]);
		cout << ans << '\n';
		exit(0);
	}
}

int dp[maxn][101];
int dx[maxn][101];
int rl[maxn*2];
int rr[maxn*2];


void setIO(string s) {
	ios_base::sync_with_stdio(0); cin.tie(0); 
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

int main()
{
	setIO("lifeguards");
	//cppio();
	cin >> n >> k; rrep(i, n) cin >> a[i].x >> a[i].y;
	zip();
	inc();

	sort(a+1, a+n+1, [](const pp& a, const pp& b){ return a.y < b.y; });
	rrep(i, n) rl[a[i].y] = rr[a[i].y] = i;
	rrep(i, 2*n-1) if (!rl[i]) rl[i] = rl[i-1];
	for(int i=xn-2; 0<=i; --i) if (!rr[i]) rr[i] = rr[i+1];

	const int inf = 1e9;
	fill(dp[0]+1, dp[0]+k+1, -inf);
	fill(dx[0]+1, dx[0]+k+1, -inf);
	rrep(i, n) {
		int l, r; tie(l, r) = a[i];
		fill(dp[i], dp[i]+k+1, -inf);
		// Case 1: [..--] [l--r]
		{ int bl = rl[l];
			for(int j=0; j+i-bl-1<=k; ++j) if (dx[bl][j] != -inf) dp[i][j+i-bl-1] = max(dp[i][j+i-bl-1], dx[bl][j] + x[r]-x[l]);
		}
		// Case 2: [.. [l--]--r]
		{ int br = rr[l];
		if (br && br != i) {
			rep(j, k+1) if (dp[br][j] != -inf) dp[i][j] = max(dp[i][j], dp[br][j] + x[r]-x[a[br].y]);
		} }

		if (i-1 <= k)
			dp[i][i-1] = max(dp[i][i-1], x[r]-x[l]);

		rrep(j, k)
			dx[i][j] = max(dx[i-1][j-1], dp[i][j]);
		dx[i][0] = dp[i][0];
	}

	int ans = 0;
	for(int i=max(1, n-k); i<=n; ++i)
		ans = max(ans, dx[i][k-(n-i)]);
	cout << ans << '\n';
	return 0;
}
