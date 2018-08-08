#include <cstdio>

int adist[101][101];
int bdist[101][101];

int n,m;

int max(int a,int b){ return a<b?b:a; }
int min(int a,int b){ return a>b?b:a; }

char dyn[101][101][201];
int time[101][101][201];

int main()
{
	freopen("meeting.in","r",stdin);
	freopen("meeting.out","w",stdout);
	scanf("%d%d",&n,&m);
	int a,b,c,d;
	int i,j;
	for(i=0;i<=100;++i){
		for(j=0;j<=100;++j) adist[i][j]=bdist[i][j]=1e9;
	}
	for(;m--;){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		adist[a][b]=c;
		bdist[a][b]=d;
	}
	int k,l;
	dyn[1][1][100]=1;
	for(i=1;i<=n;++i) for(j=1;j<=n;++j) for(k=0;k<=200;++k) time[i][j][k]=2e9;
	time[1][1][100]=0;
	for(i=1;i<=n;++i){
		for(j=1;j<=n;++j){
			if(i==1 && j==1) continue;
			for(k=1;k<i;++k){
				if(adist[k][i]!=1e9){
					for(l=0;l<=200-adist[k][i];++l){
						if(dyn[k][j][l]==1) {
							dyn[i][j][l+adist[k][i]]=1;
							time[i][j][l+adist[k][i]]=min(time[i][j][l+adist[k][i]],time[k][j][l]+adist[k][i]);
						}
					}
				}
			}
			for(k=1;k<j;++k){
				if(bdist[k][j]!=1e9){
					for(l=bdist[k][j];l<=200;++l){
						if(dyn[i][k][l]==1) {
							dyn[i][j][l-bdist[k][j]]=1;
							time[i][j][l-bdist[k][j]]=min(time[i][j][l-bdist[k][j]],time[i][k][l]+bdist[k][j]);
						}
					}
				}
			}
		}
	}
	if(dyn[n][n][100]){
		printf("%d\n",time[n][n][100]/2);
	} else puts("IMPOSSIBLE");
	return 0;
}
