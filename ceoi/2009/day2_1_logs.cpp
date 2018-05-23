#include <cstdio>
#include <algorithm>
using namespace std;

int n,m;

char buf[1510];
int cnt[1510];

int ind[1510];
int rev[1510];

int main()
{
    scanf("%d%d ",&n,&m);
    int i,j;
    for(i=0;i<m;++i) ind[i]=rev[i]=i;
    int ans=0, aa;
    for(i=0;i<n;++i){
        fgets(buf, 1510, stdin);
        int nzc=0;
        for(j=0;j<m;++j){
            if(buf[j]==48) {
                ++nzc;
                cnt[j]=0;
            }
            else {
                ++cnt[j];
            }
        }
        int czc=0;
        for(j=m-1;0<=j;--j){
            if(buf[rev[j]]==48){
                ++czc;
                ind[rev[j]]=czc-1;
            } else {
                ind[rev[j]]+=czc;
            }
        }
        for(j=0;j<m;++j){
            rev[ind[j]]=j;
            aa=(m-ind[j])*cnt[j];
            if(ans<aa) ans=aa;
        }
    }
    printf("%d\n",ans);
    return 0;
}

