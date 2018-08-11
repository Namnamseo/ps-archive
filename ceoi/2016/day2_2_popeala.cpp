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

int n, t, s;

int ps[20001];
int pl[51][20001];

char _buf[20010];
void in(){
	read(n, t, s);
	for(int i=1; i<=t; ++i){
		read(ps[i]); ps[i] += ps[i-1];
	}
	for(int i=0; i<n; ++i){
		scanf("%s", _buf + 1);
		for(int j=1; j<=t; ++j){
			if(_buf[j] == '1')
				pl[i][j] = pl[i][j-1] + 1;
		}
	}
}

ll dpr[2][20001];
ll *dp = dpr[0], *bef = dpr[1];

const ll inf = 1ll<<40;
ll tmp[52][20001];

int ls[20001][52];

int main()
{
	in();
	fill(dp+1, dp+t+1, inf);
	swap(dp, bef);
	
	for(int i=1; i<=t; ++i){
		for(int j=1; j<=n; ++j) ls[i][j] = pl[j-1][i];
		ls[i][0] = 0; ls[i][n+1] = i;
		sort(ls[i], ls[i]+n+2);
	}
	
	for(int ts=1; ts<=s; ++ts){
		for(int c=0; c<=n+1; ++c){
			fill(tmp[c], tmp[c]+ts-1, inf);
			for(int i=ts-1; i<=t; ++i){
				tmp[c][i] = bef[i] - c*ps[i];
				if(i-1 >= 0) tmp[c][i] = min(tmp[c][i], tmp[c][i-1]);
			}
		}
		
		fill(dp, dp+ts, inf);
		for(int i=ts; i<=t; ++i){
			ll d = inf;
			for(int c=0; c<=n; ++c){
				d = min(d, tmp[n-c][i-ls[i][c]-1] + (n-c)*ps[i]);
			}
			dp[i] = d;
		}
		printf("%lld\n", dp[t]);
		swap(dp, bef);
	}
	return 0;
}
