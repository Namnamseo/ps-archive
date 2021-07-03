#include <cstdio>
int n;
char map[502][502];
int dp[2][501][501];

int modder=1000000007;

int main()
{
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%s",map[i]+1);
	if(map[1][1]!=map[n][n]){ puts("0"); return 0; }
	dp[1][1][1]=1;
	int ox,oy;
	int cx,cy;
	int cur=0;
	for(i=2;i<=n;++i){
		for(j=0;j<=500;++j) for(k=0;k<=500;++k) dp[cur][j][k]=0;
		for(j=1;j<=i;++j){
			cx=j; cy=i-j+1;
			for(k=1;k<=i;++k){
				ox=n+1-k; oy=n+1-(i-k+1);
				if(map[cx][cy]==map[ox][oy]){
					if(cy-1>=1 && oy+1<=n) dp[cur][j][k]+=dp[cur^1][j  ][k  ], dp[cur][j][k]%=modder;
					if(cy-1>=1 && ox+1<=n) dp[cur][j][k]+=dp[cur^1][j  ][k-1], dp[cur][j][k]%=modder;
					if(cx-1>=1 && oy+1<=n) dp[cur][j][k]+=dp[cur^1][j-1][k  ], dp[cur][j][k]%=modder;
					if(cx-1>=1 && ox+1<=n) dp[cur][j][k]+=dp[cur^1][j-1][k-1], dp[cur][j][k]%=modder;
				}
			}
		}
		cur^=1;
	}
	int ans=0;
	for(i=1;i<=n;++i) ans+=dp[1-cur][i][n-i+1], ans%=modder;
	printf("%d\n",ans);
	return 0;
}
