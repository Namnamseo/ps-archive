#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
void read(pp& x){ scanf("%d%d",&x.first, &x.second); }
void read(pll& x){ scanf("%lld%lld",&x.first, &x.second); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
void cppio(){ ios_base::sync_with_stdio(0); cin.tie(0); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

const int maxn = int(1e6) + 10;

int n;

bool vis[200][200];
int x, y;

int ans = 0;

int dx[6] = {0, 1, 1, 0, -1, -1};
int dy[6] = {1, 0, 0, -1, 0, 0};

void dfs(int step, int ld) {
	if(step == n) {
		ans += vis[x][y];
		return;
	}
	if(vis[x][y]) return;
	vis[x][y] = 1;
	if(step == 0) {
		y += 1;
		dfs(1, 0);
		y += 0;
	} else {
		for(int df:{1, 5}) {
			int d = (ld+df)%6;
			x += dx[d]; y += dy[d];
			dfs(step+1, d);
			x -= dx[d]; y -= dy[d];
		}
	}
	vis[x][y] = 0;
}

int main()
{
	cppio();
	cin >> n;
	++n;
	x = y = 100;
	dfs(0, 0);
	cout << ans << endl;
	return 0;
}
