#include<cstdio>
using namespace std;
long long S[100001];
long long dt[2][100001];
int sel[201][100001];
struct Elem{long long a,b; int index;};
Elem data[100010];
int s,e;
double crossX(long long pa,long long pb,long long qa,long long qb){ return ((double)qb-pb)/((double)pa-qa); }
void add(long long a,long long b,int index)
{
    if(s!=e)
    {
        if(data[e-1].a==a)
        {
            if(data[e-1].b<b) data[e-1]={a,b,index};
            return;
        }
    }
    while(e-s>=2)
    {
        if(crossX(data[e-2].a,data[e-2].b,data[e-1].a,data[e-1].b)>=crossX(data[e-1].a,data[e-1].b,a,b))
            e--;
        else break;
    }
    data[e++]={a,b,index};
}
void get_min(long long x)
{
    while(e-s>=2)
    {
        if(data[s].a*x+data[s].b<data[s+1].a*x+data[s+1].b)
            s++;
        else break;
    }
}
int ans[100010];
int main()
{
    int N,K;
    scanf("%d %d",&N,&K);
    for(int i=1,x;i<=N;i++)
        scanf("%d",&x),S[i]=S[i-1]+x;
    for(int i=2;i<=K+1;++i)
    {
        s=e=0;
        add(S[i-1],dt[(i-1)&1][i-1]-S[i-1]*S[i-1],i-1);
        for(int j=i;j<=N;++j)
        {
            get_min(S[j]);
            dt[i&1][j]=data[s].a*S[j]+data[s].b;
            sel[i][j]=data[s].index;
            add(S[j],dt[(i-1)&1][j]-S[j]*S[j],j);
        }
    }
    printf("%lld\n",dt[(K+1)&1][N]);
    int now_i=K+1,now_j=sel[K+1][N];
    while(now_i!=1)
    {
        ans[now_i]=now_j;
        now_i--;
        now_j=sel[now_i][now_j];
    }
    for(int i=2;i<=K+1; ++i) printf("%d ",ans[i]);
    return 0;
}
