#include <cstdio>

int map[110][110];
int cnt[110];

int main()
{
    int n;
    scanf("%d",&n);
    int t;
    int a,b,w,h,i,j;
    for(t=0;t<n;++t){
        scanf("%d%d%d%d",&a,&b,&w,&h);
        for(i=0;i<w;++i) for(j=0;j<h;++j) map[a+i][b+j]=t+1;
    }
    for(i=0;i<=101;i++){
        for(j=0;j<=101;++j){
            ++cnt[map[i][j]];
        }
    }
    for(i=0;i<n;++i) printf("%d\n",cnt[i+1]);
    return 0;
}
