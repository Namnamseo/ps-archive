#include <cstdio>
#include <vector>
#define pb push_back

using namespace std;

vector<int> e[200010];

int n,m;

int q[200010];
bool ex[200010];

int par[200010];
int sz[200010];

void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args> void read(T& a,Args&... b){ read(a); read(b...); }

int R(int x){ return (x==par[x])?x:(par[x]=R(par[x])); }

void join(int a,int b){
    a=R(a); b=R(b);
    if(a==b) return;
    sz[a]+=sz[b]; par[b]=a;
}

bool ans[200010];

int main()
{
    read(n,m);
    int i;
    for(i=1; i<=n; ++i) par[i]=i, sz[i]=1;
    for(;m--;){
        int a,b;
        read(a,b);
        e[a].pb(b); e[b].pb(a);
    }
    for(i=n;1<=i;--i) read(q[i]);
    int base=q[1];
    for(i=1;i<=n;++i){
        int x=q[i];
        for(int& y:e[x]){
            if(ex[y]){
                join(x,y);
            }
        }
        ex[x]=true;
        ans[i]=(sz[R(base)]==i);
    }
    for(i=n;1<=i;--i) puts(ans[i]?"YES":"NO");
    return 0;
}
