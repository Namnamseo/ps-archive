#include <cstdio>

int n,m,k;

int data[20010];

typedef long long ll;

ll dp[20010];

template<typename T> inline T max(T a,T b){ return b<a?a:b; }
template<typename T> inline T min(T a,T b){ return a<b?a:b; }

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int i,j;
	int Mx, mn;
	for(i=1;i<=n;++i){
		scanf("%d",data+i);
		Mx=mn=data[i];
		dp[i]=(1LL<<61);
		for(j=i;j && i-j<m;--j){
			Mx=max(Mx,data[j]);
			mn=min(mn,data[j]);
			dp[i]=min(dp[i], dp[j-1]+k+ll(i-j+1)*(Mx-mn));
		}
	}
	printf("%lld",dp[n]);
	return 0;
}
