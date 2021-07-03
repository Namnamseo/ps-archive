#include <cstdio>
#include <algorithm>
using namespace std;

int n,k;

int data[1010];

int main()
{
    freopen("diamond.in","r",stdin);
    freopen("diamond.out","w",stdout);
    scanf("%d%d",&n,&k);
    int i;
    for(i=1;i<=n;++i) scanf("%d",data+i);
    sort(data+1,data+n+1);
    int j=1;
    int ans=0;
    for(i=1;i<=n;++i){
        while(j<=i && data[i]>data[j]+k) ++j;
        ans=max(ans,i-j+1);
    }
    printf("%d\n",ans);
    return 0;
}
