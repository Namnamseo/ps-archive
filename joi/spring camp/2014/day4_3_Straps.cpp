#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define x first
#define y second

int n;

int h, y;

vector<pp> ng;

int bt[2010], bn;

ll dp[2010];
const ll inf = 1ll<<60;

int main()
{
	read(n);
	for(;n--;){
		int hole, ureshi;
		read(hole, ureshi);
		if(ureshi > 0){
			if(hole == 0) bt[bn++] = ureshi;
			else y += ureshi, h += hole-1;
		} else if(ureshi == 0){
			if(hole > 1) h += hole-1;
		} else if(hole > 1){
			ng.eb(hole-1, ureshi);
		}
	}
	sort(bt, bt+bn, greater<int>());
	n = 2000;
	for(int i=1; i<=n; ++i) bt[i] += bt[i-1];
	
	fill(dp, dp+n+1, -inf);
	dp[min(n, h)] = 0;
	
	for(auto t:ng){
		int step, val; tie(step, val) = t;
		for(int i=n-1; 0<=i; --i){
			int ni = min(n, i+step);
			dp[ni] = max(dp[ni], dp[i]+val);
		}
	}
	
	ll ans = -inf;
	for(int i=0; i<=n; ++i) ans = max(ans, dp[i] + bt[i]);
	printf("%lld\n", ans+y);
	return 0;
}
