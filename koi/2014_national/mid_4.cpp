#include <cstdio>
#include <algorithm>
#define x first
#define y second
using namespace std;
int n;
typedef pair<int,int> pp;
pair<pp,int> d[3010];
int xs[3010],x;
int ys[3010],y;
int v[3010];
pp p[3010];
int m=4096;
long long s[8192];
long long l[8192];
long long r[8192];
long long a[8192];
bool    non[8192];
void u(int pos,int val){
    pos+=m;
    s[pos]+=val;
    l[pos]=r[pos]=a[pos]=s[pos];
    while(pos/2){
        pos/=2;
        s[pos]=s[pos*2]+s[pos*2+1];
        l[pos]=max(l[pos*2  ],s[pos*2]+l[pos*2+1]);
        r[pos]=max(r[pos*2+1],s[pos*2+1]+r[pos*2]);
        a[pos]=max(a[pos*2],max(a[pos*2+1],r[pos*2]+l[pos*2+1]));
    }
}
long long ans;
int main()
{
    scanf("%d",&n);
    int i,j;
    for(i=0;i<n;++i) scanf("%d%d%d",&d[i].x.x,&d[i].x.y,&d[i].y),
                     xs[i]=d[i].x.x, ys[i]=d[i].x.y;
    sort(d,d+n);
    for(i=0;i<n;++i) v[i]=d[i].y, p[i]=d[i].x;
    sort(xs,xs+n); sort(ys,ys+n);
    x=unique(xs,xs+n)-xs; y=unique(ys,ys+n)-ys;
    for(i=0;i<n;++i) p[i].x=lower_bound(xs,xs+x,p[i].x)-xs,
                     p[i].y=lower_bound(ys,ys+y,p[i].y)-ys;
    int curx=-1;
    for(i=0;i<n;++i){
        if(curx==p[i].x) continue;
        curx=p[i].x;
        for(j=1;j<8192;++j) l[j]=r[j]=a[j]=-(1LL<<40), s[j]=0;
        for(j=i;j<n;++j){
            u(p[j].y,v[j]);
            if(j==n-1 || p[j].x!=p[j+1].x) ans=max(ans,a[1]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
