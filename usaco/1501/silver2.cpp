#include <cstdio>

int mincost[1010][1010];
int mincnt [1010][1010];
typedef long long ll;
int lists[101];
int cntto[1010];
int a,b,n;
ll mindist   [1010];
int queue [1000010];

int min(int a,int b) { return a>b?b:a; }

int main()
{
	freopen("cowroute.in" ,"r",stdin);
	freopen("cowroute.out","w",stdout);
	scanf("%d%d%d",&a,&b,&n);
	int cost,ls,i,j;
	for(i=1;i<=1000;++i) for(j=1;j<=1000;++j) mincost[i][j]=2e9;
	for(;n--;){
		scanf("%d%d",&cost,&ls);
		for(i=0;i<ls;++i) scanf("%d",lists+i);
		for(i=1;i<ls;++i) for(j=0;j<i;++j) {
			if(mincost[lists[j]][lists[i]]>cost){
				mincost[lists[j]][lists[i]]=cost;
				mincnt [lists[j]][lists[i]]=i-j;
			} else if(mincost[lists[j]][lists[i]]==cost){
				mincnt [lists[j]][lists[i]]=min(mincnt [lists[j]][lists[i]],i-j);
			}
		}
	}
	for(i=1;i<=1000;++i) mindist[i]=2000000000000000LL, cntto[i]=2e9;
	mindist[a]=0;
	queue[0]=a; cntto[a]=0;
	int head=1, tail=0;
	int cur;
	while(tail<head){
		cur=queue[tail++];
		for(i=1;i<=1000;++i){
			if(mincost[cur][i]!=2e9)
			{
				if(mindist[cur]+mincost[cur][i]<mindist[i]){
					mindist[i]=mindist[cur]+mincost[cur][i];
					cntto  [i]=cntto  [cur]+mincnt [cur][i];
					queue[head++]=i;
				} else if(mindist[cur]+mincost[cur][i]==mindist[i] && cntto[i]>cntto[cur]+mincnt[cur][i]){
					cntto[i]  = cntto[cur]  + mincnt [cur][i];
					queue[head++]=i;
				}
			}
		}
	}
	if(cntto[b]==2e9) puts("-1 -1");
	else printf("%lld %d\n",mindist[b],cntto[b]);
	return 0;
}
