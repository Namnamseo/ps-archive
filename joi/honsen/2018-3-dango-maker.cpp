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

int n, m;
char s[3010][3010];

int dp[6010][3010][2];

bool is(int i, int j, char c){
	return 1<=i && i<=n && 1<=j && j<=m && s[i][j] == c;
}

int main()
{
	read(n, m);
	for(int i=1; i<=n; ++i) scanf("%s", s[i]+1);
	
	int ans = 0;
	for(int s=2; s<=n+m-2; ++s){
		int rm=0;
		for(int i=1; i<=n; ++i){
			dp[s][i][0] = max({dp[s][i][0], dp[s][i-1][0], dp[s][i-2][1]});
			dp[s][i][1] = max(dp[s][i][1], dp[s][i-1][1]);
			int j=s-i;
			if(j<1 || j>m) continue;
			if(is(i, j, 'R') && is(i, j+1, 'G') && is(i, j+2, 'W')){
				dp[s][i][0] = max(dp[s][i][0], dp[s][i-1][0]+1);
			}
			if(is(i, j, 'R') && is(i+1, j, 'G') && is(i+2, j, 'W')){
				dp[s][i][1] = max({dp[s][i][1], dp[s][i-1][1]+1, dp[s][i-1][0]+1});
			}
			rm=max({rm, dp[s][i][0], dp[s][i][1]});
		}
		ans += rm;
	}
	
	printf("%d\n", ans);
	return 0;
}
