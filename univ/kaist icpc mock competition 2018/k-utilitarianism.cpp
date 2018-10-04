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
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define sz(x) (int)(x).size()

int n, k;

vector<pp> e[250010];

ll dp[250010][2];
int par[250010];
ll p;
void dfs(ll x){
	dp[x][0]=0;
    dp[x][1]=0;

	ll dfm = -(1ll<<60);

	for(auto& tmp:e[x]){
		int y, d; tie(y, d) = tmp;
		if(y == par[x]) continue;
		par[y]=x; dfs(y);
		dp[x][0] += dp[y][1];
		dp[x][1] += dp[y][1];
		dfm = max(dfm, -dp[y][1] + dp[y][0] + (d-p));
	}

	dp[x][1] += dfm;
    dp[x][1] = max(dp[x][1], dp[x][0]);
}

ll f(ll pen){
	p = pen;
	dfs(1);
	return dp[1][1];
}

int main()
{
	read(n, k);
	for(int i=1,a,b,c; i<n; ++i){
		read(a,b,c);
		e[a].eb(b,c); e[b].eb(a,c);
	}

	ll l=ll(-1e12), r=ll(1e12);
	while(l+1<r){
		ll md=((l+r)>>1);
		ll df = f(md+1)-f(md);
		if(-df > k) l = md;
		else r = md;
	}
    ll vl=f(l), vr=f(r), vrr=f(r+1);
	if((vl-vr)>=k && k>=(vr-vr)) printf("%lld\n", f(r)+r*k);
    else puts("Impossible");
	return 0;
}

