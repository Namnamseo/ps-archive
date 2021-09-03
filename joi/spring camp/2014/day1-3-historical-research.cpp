#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;

int imp[100010];
int pri[100010];
ll  ans[100010];
int in;
int data[100010];
int bck;

struct qr{int ind,l,r; } query[100010];

bool comp(const qr& a,const qr& b) { return a.l/bck==b.l/bck?a.r<b.r:a.l<b.l;}

int n,q;

ll tree[262144];

inline void add(int ind,int val){
    ind+=131072; tree[ind]+=val; ind/=2;
    while(ind) tree[ind]=max(tree[ind*2],tree[ind*2+1]), ind/=2;
}

int main()
{
    scanf("%d%d",&n,&q); int i; for(i=1;i<=n;++i) scanf("%d",data+i),imp[i-1]=data[i];
    bck=300;
    sort(imp,imp+n);in=unique(imp,imp+n)-imp;
    for(i=1;i<=n;++i) pri[i]=lower_bound(imp,imp+in,data[i])-imp;
    int a,b;
    for(i=0;i<q;++i) scanf("%d%d",&a,&b),query[i].ind=i,query[i].l=a,query[i].r=b;
    sort(query,query+q,comp);
    int l=query[0].l, r=query[0].r;
    for(i=l;i<=r;++i) add(pri[i],data[i]);
    ans[query[0].ind]=tree[1];
    for(i=1;i<q;++i){
        while(query[i].l<=l-1) --l,add(pri[l],data[l]);
        while(r+1<=query[i].r) ++r,add(pri[r],data[r]);
        while(l<query[i].l) add(pri[l],-data[l]),++l;
        while(query[i].r<r) add(pri[r],-data[r]),--r;
        ans[query[i].ind]=tree[1];
    }
    for(i=0;i<q;++i) printf("%lld\n",ans[i]);
    return 0;
}
