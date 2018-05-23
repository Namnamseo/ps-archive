#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define pb push_back

int n, q;

typedef tuple<int,int,int> tp;

tp qr[300010];
vector<int> edge[100010];
int par[20][100010];
int dep[100010];

struct ASDF {
    void init(){
        for(int i=1; i<20; ++i) for(int j=1; j<=n; ++j)
            par[i][j] = par[i-1][par[i-1][j]];
    }
    
    int lca(int a, int b){
        if(dep[a] > dep[b]) swap(a, b);
        for(int i=19; 0<=i; --i) if(1&((dep[b]-dep[a])>>i)) b=par[i][b];
        for(int i=19; 0<=i; --i){
            if(par[i][a] != par[i][b]) a=par[i][a], b=par[i][b];
        }
        if(a^b) a=par[0][a];
        return a;
    }
} LCA;

struct UFO {
    int par[100010];
    void init(){ for(int i=1; i<=n; ++i) par[i]=i; }
    int root(int x){ return (par[x]==x)?x:(par[x]=root(par[x])); }
    void join(int a,int b){
        a=root(a); b=root(b);
        if(dep[a]>dep[b]) swap(a,b);
        par[b]=a;
    }
} uf, uf2;

int in[100010];
int out[100010];
int nt;

void dfs(int x){
    in[x] = ++nt;
    for(int y:edge[x]){
        if(par[0][x] == y) continue;
        par[0][y] = x;
        dep[y] = dep[x]+1;
        dfs(y);
    }
    out[x] = nt;
}

struct SEG {
    static const int M = 131072;
    int tree[M<<1];

    void upd(int l,int r,int val){
        l+=M; r+=M;
        while(l<=r){
            if(l%2==1) tree[l++] += val;
            if(r%2==0) tree[r--] += val;
            l>>=1; r>>=1;
        }
    }
    
    int get(int pos){
        pos=in[pos];
        pos+=M;
        int ret=0;
        while(pos) ret+=tree[pos], pos>>=1;
        return ret;
    }
} seg;

void goup(int x,int to){
    while(true){
        x=uf.root(x);
        if(dep[x] <= dep[to]) break;
        seg.upd(in[x], out[x], -1);
        uf.join(x, par[0][x]);
        x=par[0][x];
    }
}

int main()
{
    read(n, q);
    uf.init();
    for(int i=1; i<=q; ++i){
        int t, a, b;
        read(t, a, b);
        if(t == 1){
            if(uf.root(a) != uf.root(b)){
                edge[a].pb(b);
                edge[b].pb(a);
                uf.join(a, b);
            }
        }
        qr[i] = make_tuple(t, a, b);
    }
    for(int i=1; i<=n; ++i) if(!in[i]) dfs(i);
    for(int i=1; i<=n; ++i) if(par[0][i]) seg.upd(in[i], out[i], 1);
    
    uf.init();
    uf2.init();
    LCA.init();
    //seg.upd(1, nt, 1);
    for(int i=1; i<=q; ++i){
        int t, a, b; tie(t, a, b) = qr[i];
        if(t == 1){
            if(uf2.root(a) == uf2.root(b)){
                int l=LCA.lca(a, b);
                goup(a, l);
                goup(b, l);
            } else {
                uf2.join(a, b);
            }
        } else {
            if(uf2.root(a) != uf2.root(b)){
                puts("-1");
            } else {
                int l=LCA.lca(a, b);
                printf("%d\n", seg.get(a) + seg.get(b) - seg.get(l)*2);
            }
        }
    }
    return 0;
}
