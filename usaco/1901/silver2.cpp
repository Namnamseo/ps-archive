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

int n;

char s[1010][1010];
bool vis[1010][1010];

int sz, per;

const int dx[5] = {0,1,0,-1,0}, *dy = dx+1;

void dfs(int x, int y){
	if(vis[x][y]) return;
	vis[x][y] = 1;
	++sz;
	for(int d=0; d<4; ++d){
		int nx=x+dx[d], ny=y+dy[d];
		if(nx<1 || ny<1 || nx>n || ny>n){
			++per;
			continue;
		}
		if(s[nx][ny] == '.') ++per;
		else if(!vis[nx][ny]) dfs(nx, ny);
	}
}

int main()
{
	cppio();
	cin >> n;
	rrep(i, n) cin >> (s[i]+1);

	pp ans(0, 0);

	rrep(i, n) rrep(j, n) if(s[i][j] == '#' && !vis[i][j]){
		sz = per = 0;
		dfs(i, j);
		ans = max(ans, pp(sz, -per));
	}

	cout << ans.x << ' ' << -ans.y << endl;
	return 0;
}
